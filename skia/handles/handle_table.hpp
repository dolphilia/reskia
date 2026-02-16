#ifndef RESKIA_STATIC_HANDLE_TABLE_HPP
#define RESKIA_STATIC_HANDLE_TABLE_HPP

#include <cstdint>
#include <map>
#include <mutex>
#include <set>
#include <utility>
#include <vector>

namespace reskia::static_registry {

template <typename T>
class HandleTable {
public:
    int create(T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        const int slot = acquire_slot_locked();
        entries_.emplace(slot, std::move(value));
        return encode_handle(slot, generations_[slot]);
    }

    // Strict set: fails when key does not exist.
    bool set(int key, T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        const SlotRef slot = resolve_slot_locked(key);
        if (!slot.valid) {
            return false;
        }
        auto it = entries_.find(slot.slot);
        if (it == entries_.end()) {
            return false;
        }
        it->second = std::move(value);
        return true;
    }

    // Legacy-compatible helper while call sites migrate to strict set().
    void set_or_insert(int key, T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        const SlotRef slot = resolve_slot_locked(key);
        if (slot.valid) {
            auto it = entries_.find(slot.slot);
            if (it == entries_.end()) {
                return;
            }
            it->second = std::move(value);
            return;
        }
        // Fallback: treat non-generation key as a no-op to preserve strict behavior.
    }

    T* get_ptr(int key) {
        std::lock_guard<std::mutex> lock(mutex_);
        const SlotRef slot = resolve_slot_locked(key);
        if (!slot.valid) {
            return nullptr;
        }
        auto it = entries_.find(slot.slot);
        if (it == entries_.end()) {
            return nullptr;
        }
        return &it->second;
    }

    const T* get_ptr(int key) const {
        std::lock_guard<std::mutex> lock(mutex_);
        const SlotRef slot = resolve_slot_locked(key);
        if (!slot.valid) {
            return nullptr;
        }
        auto it = entries_.find(slot.slot);
        if (it == entries_.end()) {
            return nullptr;
        }
        return &it->second;
    }

    bool erase(int key) {
        std::lock_guard<std::mutex> lock(mutex_);
        const SlotRef slot = resolve_slot_locked(key);
        if (!slot.valid) {
            return false;
        }
        auto it = entries_.find(slot.slot);
        if (it == entries_.end()) {
            return false;
        }
        entries_.erase(it);
        advance_generation_locked(slot.slot);
        available_slots_.insert(slot.slot);
        return true;
    }

    bool contains(int key) const {
        std::lock_guard<std::mutex> lock(mutex_);
        const SlotRef slot = resolve_slot_locked(key);
        if (!slot.valid) {
            return false;
        }
        return entries_.find(slot.slot) != entries_.end();
    }

    T take_or_default(int key) {
        std::lock_guard<std::mutex> lock(mutex_);
        const SlotRef slot = resolve_slot_locked(key);
        if (!slot.valid) {
            return T{};
        }
        auto it = entries_.find(slot.slot);
        if (it == entries_.end()) {
            return T{};
        }
        return std::move(it->second);
    }

private:
    static constexpr uint32_t kSlotBits = 20;
    static constexpr uint32_t kSlotMask = (1u << kSlotBits) - 1u;
    static constexpr uint32_t kGenerationMask = (1u << (31u - kSlotBits)) - 1u;

    struct SlotRef {
        int slot = -1;
        bool valid = false;
    };

    static int encode_handle(int slot, uint32_t generation) {
        const uint32_t encoded = (generation << kSlotBits) | static_cast<uint32_t>(slot);
        return static_cast<int>(encoded);
    }

    int acquire_slot_locked() {
        if (!available_slots_.empty()) {
            auto it = available_slots_.begin();
            const int slot = *it;
            available_slots_.erase(it);
            return slot;
        }
        const int slot = next_slot_++;
        generations_.push_back(1u);
        return slot;
    }

    SlotRef resolve_slot_locked(int handle) const {
        const uint32_t encoded = static_cast<uint32_t>(handle);
        const uint32_t generation = (encoded >> kSlotBits) & kGenerationMask;
        if (generation == 0u) {
            return {};
        }
        const int slot = static_cast<int>(encoded & kSlotMask);
        if (slot < 0 || slot >= next_slot_) {
            return {};
        }
        if (generations_[slot] != generation) {
            return {};
        }
        return {slot, true};
    }

    void advance_generation_locked(int slot) {
        uint32_t next_generation = (generations_[slot] + 1u) & kGenerationMask;
        if (next_generation == 0u) {
            next_generation = 1u;
        }
        generations_[slot] = next_generation;
    }

    mutable std::mutex mutex_;
    std::set<int> available_slots_;
    std::map<int, T> entries_;
    std::vector<uint32_t> generations_;
    int next_slot_ = 0;
};

}  // namespace reskia::static_registry

#endif  // RESKIA_STATIC_HANDLE_TABLE_HPP
