#include "include/utils/SkLogHandler.h"
#include "include/private/SkLog.h"

#include <atomic>
#include <cstdio>
#include <cstring>
#include <thread>

namespace {
class Handler final : public SkLogHandler {
public:
    Handler(std::atomic<int>& calls, std::atomic<int>& destroyed, std::atomic<bool>& valid)
        : fCalls(calls), fDestroyed(destroyed), fValid(valid) {}
    ~Handler() override { ++fDestroyed; }
    void onLog(SkLogPriority priority, const char format[], va_list args) override {
        char message[64];
        std::vsnprintf(message, sizeof(message), format, args);
        if (priority != SkLogPriority::kInfo || std::strcmp(message, "cycle 103") != 0) {
            fValid = false;
        }
        ++fCalls;
    }
private:
    std::atomic<int>& fCalls;
    std::atomic<int>& fDestroyed;
    std::atomic<bool>& fValid;
};
}

int main() {
    // Installed handler remains owned by Skia for the lifetime of this process.
    static std::atomic<int> calls{0}, destroyed{0};
    static std::atomic<bool> valid{true};
    if (SkLogHandler::GetInstance() ||
        !SkLogHandler::SetInstance(sk_make_sp<Handler>(calls, destroyed, valid))) {
        return 1;
    }
    if (SkLogHandler::SetInstance(sk_make_sp<Handler>(calls, destroyed, valid)) ||
        destroyed != 1 || !SkLogHandler::GetInstance()) {
        return 2;
    }
    auto log = [] { SkLog(SkLogPriority::kInfo, "cycle %d", 103); };
    std::thread a(log), b(log);
    a.join();
    b.join();
    if (calls != 2 || !valid || destroyed != 1) {
        return 3;
    }
    std::puts("[log-handler-smoke] PASS");
    return 0;
}
