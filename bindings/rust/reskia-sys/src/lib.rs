#![allow(non_camel_case_types)]

use std::os::raw::{c_float, c_int, c_void};

pub enum reskia_image_t {}
pub enum reskia_surface_t {}
pub enum reskia_paint_t {}
pub enum reskia_path_t {}
pub enum reskia_image_info_t {}
pub enum reskia_surface_props_t {}
pub type sk_image_t = c_int;
pub type sk_surface_t = c_int;
pub type sk_paint_t = c_int;
pub type sk_path_t = c_int;
pub type sk_image_info_t = c_int;

#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum reskia_status_t {
    Ok = 0,
    InvalidArgument = 1,
    NotFound = 2,
    InternalError = 3,
}

unsafe extern "C" {
    pub fn SkImageInfo_MakeN32Premul(width: c_int, height: c_int) -> sk_image_info_t;
    pub fn static_sk_image_info_get_ptr(key: sk_image_info_t) -> *mut c_void;
    pub fn static_sk_image_info_delete(key: sk_image_info_t);

    pub fn SkSurfaces_RasterWithoutRowBytes(
        image_info: *const reskia_image_info_t,
        props: *const reskia_surface_props_t,
    ) -> sk_surface_t;
    pub fn static_sk_surface_delete(key: sk_surface_t);
    pub fn static_sk_image_delete(key: sk_image_t);

    pub fn SkImage_width(image: *mut reskia_image_t) -> c_int;
    pub fn SkImage_height(image: *mut reskia_image_t) -> c_int;
    pub fn SkImage_uniqueID(image: *mut reskia_image_t) -> u32;
    pub fn SkImage_isOpaque(image: *mut reskia_image_t) -> bool;
    pub fn reskia_image_retain(image: *mut reskia_image_t);
    pub fn reskia_image_release(image: *mut reskia_image_t);
    pub fn reskia_image_borrow_from_handle(handle: sk_image_t) -> *mut reskia_image_t;

    pub fn SkSurface_width(surface: *mut reskia_surface_t) -> c_int;
    pub fn SkSurface_height(surface: *mut reskia_surface_t) -> c_int;
    pub fn SkSurface_makeImageSnapshot(surface: *mut reskia_surface_t) -> sk_image_t;
    pub fn reskia_surface_retain(surface: *mut reskia_surface_t);
    pub fn reskia_surface_release(surface: *mut reskia_surface_t);
    pub fn reskia_surface_borrow_from_handle(handle: sk_surface_t) -> *mut reskia_surface_t;

    pub fn SkPaint_new() -> *mut reskia_paint_t;
    pub fn reskia_paint_retain(paint: *const reskia_paint_t) -> *mut reskia_paint_t;
    pub fn reskia_paint_release(paint: *mut reskia_paint_t);
    pub fn reskia_paint_borrow_from_handle(handle: sk_paint_t) -> *mut reskia_paint_t;
    pub fn SkPaint_getStrokeWidth(paint: *mut reskia_paint_t) -> c_float;
    pub fn SkPaint_setARGB(paint: *mut reskia_paint_t, a: u8, r: u8, g: u8, b: u8);
    pub fn SkPaint_setStrokeWidth(paint: *mut reskia_paint_t, width: c_float);

    pub fn SkPath_new() -> *mut reskia_path_t;
    pub fn reskia_path_retain(path: *const reskia_path_t) -> *mut reskia_path_t;
    pub fn reskia_path_release(path: *mut reskia_path_t);
    pub fn reskia_path_borrow_from_handle(handle: sk_path_t) -> *mut reskia_path_t;
    pub fn SkPath_moveTo(path: *mut reskia_path_t, x: c_float, y: c_float) -> *mut reskia_path_t;
    pub fn SkPath_lineTo(path: *mut reskia_path_t, x: c_float, y: c_float) -> *mut reskia_path_t;
    pub fn SkPath_close(path: *mut reskia_path_t) -> *mut reskia_path_t;
    pub fn SkPath_isEmpty(path: *mut reskia_path_t) -> bool;
    pub fn SkPath_countPoints(path: *mut reskia_path_t) -> c_int;
    pub fn SkPath_interpolate(
        path: *mut reskia_path_t,
        ending: *const reskia_path_t,
        weight: c_float,
        out_path: *mut reskia_path_t,
    ) -> reskia_status_t;
}
