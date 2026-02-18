use std::fmt;
use std::marker::PhantomData;
use std::ptr::NonNull;

pub use reskia_sys as sys;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Error {
    NullReturn(&'static str),
    OperationFailed(&'static str),
    Status(sys::reskia_status_t),
}

impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::NullReturn(op) => write!(f, "reskia returned null pointer: {op}"),
            Self::OperationFailed(op) => write!(f, "reskia operation failed: {op}"),
            Self::Status(status) => write!(f, "reskia returned error status: {status:?}"),
        }
    }
}

impl std::error::Error for Error {}

pub struct Image {
    raw: NonNull<sys::reskia_image_t>,
}

pub struct BorrowedImage<'a> {
    raw: NonNull<sys::reskia_image_t>,
    _marker: PhantomData<&'a ()>,
}

impl Image {
    /// # Safety
    ///
    /// `ptr` must be a valid owned `SkImage*` pointer.
    pub unsafe fn from_raw_owned(ptr: *mut sys::reskia_image_t) -> Result<Self, Error> {
        NonNull::new(ptr)
            .map(|raw| Self { raw })
            .ok_or(Error::NullReturn("Image::from_raw_owned"))
    }

    pub fn as_ptr(&self) -> *mut sys::reskia_image_t {
        self.raw.as_ptr()
    }

    pub fn width(&self) -> i32 {
        unsafe { sys::SkImage_width(self.raw.as_ptr()) }
    }

    pub fn height(&self) -> i32 {
        unsafe { sys::SkImage_height(self.raw.as_ptr()) }
    }

    pub fn unique_id(&self) -> u32 {
        unsafe { sys::SkImage_uniqueID(self.raw.as_ptr()) }
    }

    pub fn is_opaque(&self) -> bool {
        unsafe { sys::SkImage_isOpaque(self.raw.as_ptr()) }
    }

    pub fn from_handle_retained(handle: sys::sk_image_t) -> Result<Self, Error> {
        let raw = unsafe { sys::reskia_image_borrow_from_handle(handle) };
        let raw = NonNull::new(raw).ok_or(Error::NullReturn("Image::from_handle_retained"))?;
        unsafe { sys::reskia_image_retain(raw.as_ptr()) };
        Ok(Self { raw })
    }

    /// # Safety
    ///
    /// The returned borrow is tied to `'a` and must not outlive the underlying handle storage.
    pub unsafe fn borrow_from_handle<'a>(handle: sys::sk_image_t) -> Option<BorrowedImage<'a>> {
        NonNull::new(unsafe { sys::reskia_image_borrow_from_handle(handle) }).map(|raw| {
            BorrowedImage {
                raw,
                _marker: PhantomData,
            }
        })
    }
}

impl BorrowedImage<'_> {
    pub fn as_ptr(&self) -> *mut sys::reskia_image_t {
        self.raw.as_ptr()
    }

    pub fn width(&self) -> i32 {
        unsafe { sys::SkImage_width(self.raw.as_ptr()) }
    }

    pub fn height(&self) -> i32 {
        unsafe { sys::SkImage_height(self.raw.as_ptr()) }
    }

    pub fn unique_id(&self) -> u32 {
        unsafe { sys::SkImage_uniqueID(self.raw.as_ptr()) }
    }

    pub fn is_opaque(&self) -> bool {
        unsafe { sys::SkImage_isOpaque(self.raw.as_ptr()) }
    }
}

impl Clone for Image {
    fn clone(&self) -> Self {
        unsafe { sys::reskia_image_retain(self.raw.as_ptr()) };
        Self { raw: self.raw }
    }
}

impl Drop for Image {
    fn drop(&mut self) {
        unsafe { sys::reskia_image_release(self.raw.as_ptr()) };
    }
}

pub struct Surface {
    raw: NonNull<sys::reskia_surface_t>,
}

pub struct BorrowedSurface<'a> {
    raw: NonNull<sys::reskia_surface_t>,
    _marker: PhantomData<&'a ()>,
}

pub struct CanvasRef<'a> {
    raw: NonNull<sys::reskia_canvas_t>,
    _marker: PhantomData<&'a ()>,
}

impl Surface {
    /// # Safety
    ///
    /// `ptr` must be a valid owned `SkSurface*` pointer.
    pub unsafe fn from_raw_owned(ptr: *mut sys::reskia_surface_t) -> Result<Self, Error> {
        NonNull::new(ptr)
            .map(|raw| Self { raw })
            .ok_or(Error::NullReturn("Surface::from_raw_owned"))
    }

    pub fn as_ptr(&self) -> *mut sys::reskia_surface_t {
        self.raw.as_ptr()
    }

    pub fn width(&self) -> i32 {
        unsafe { sys::SkSurface_width(self.raw.as_ptr()) }
    }

    pub fn height(&self) -> i32 {
        unsafe { sys::SkSurface_height(self.raw.as_ptr()) }
    }

    pub fn from_handle_retained(handle: sys::sk_surface_t) -> Result<Self, Error> {
        let raw = unsafe { sys::reskia_surface_borrow_from_handle(handle) };
        let raw = NonNull::new(raw).ok_or(Error::NullReturn("Surface::from_handle_retained"))?;
        unsafe { sys::reskia_surface_retain(raw.as_ptr()) };
        Ok(Self { raw })
    }

    pub fn make_image_snapshot(&self) -> Result<Image, Error> {
        let handle = unsafe { sys::SkSurface_makeImageSnapshot(self.raw.as_ptr()) };
        Image::from_handle_retained(handle)
    }

    pub fn borrow_canvas(&mut self) -> Result<CanvasRef<'_>, Error> {
        let raw = unsafe { sys::reskia_surface_borrow_canvas(self.raw.as_ptr()) };
        let raw = NonNull::new(raw).ok_or(Error::NullReturn("Surface::borrow_canvas"))?;
        Ok(CanvasRef {
            raw,
            _marker: PhantomData,
        })
    }

    /// # Safety
    ///
    /// The returned borrow is tied to `'a` and must not outlive the underlying handle storage.
    pub unsafe fn borrow_from_handle<'a>(handle: sys::sk_surface_t) -> Option<BorrowedSurface<'a>> {
        NonNull::new(unsafe { sys::reskia_surface_borrow_from_handle(handle) }).map(|raw| {
            BorrowedSurface {
                raw,
                _marker: PhantomData,
            }
        })
    }
}

impl BorrowedSurface<'_> {
    pub fn as_ptr(&self) -> *mut sys::reskia_surface_t {
        self.raw.as_ptr()
    }

    pub fn width(&self) -> i32 {
        unsafe { sys::SkSurface_width(self.raw.as_ptr()) }
    }

    pub fn height(&self) -> i32 {
        unsafe { sys::SkSurface_height(self.raw.as_ptr()) }
    }
}

impl CanvasRef<'_> {
    pub fn clear_argb(&mut self, a: u8, r: u8, g: u8, b: u8) {
        let color =
            (u32::from(a) << 24) | (u32::from(r) << 16) | (u32::from(g) << 8) | u32::from(b);
        unsafe { sys::SkCanvas_clearColor(self.raw.as_ptr(), color) };
    }

    pub fn draw_circle(&mut self, cx: f32, cy: f32, radius: f32, paint: &Paint) {
        unsafe { sys::SkCanvas_drawCircleAt(self.raw.as_ptr(), cx, cy, radius, paint.as_ptr()) };
    }

    pub fn draw_path(&mut self, path: &Path, paint: &Paint) {
        unsafe { sys::SkCanvas_drawPath(self.raw.as_ptr(), path.as_ptr(), paint.as_ptr()) };
    }
}

impl Clone for Surface {
    fn clone(&self) -> Self {
        unsafe { sys::reskia_surface_retain(self.raw.as_ptr()) };
        Self { raw: self.raw }
    }
}

impl Drop for Surface {
    fn drop(&mut self) {
        unsafe { sys::reskia_surface_release(self.raw.as_ptr()) };
    }
}

pub struct Paint {
    raw: NonNull<sys::reskia_paint_t>,
}

pub struct BorrowedPaint<'a> {
    raw: NonNull<sys::reskia_paint_t>,
    _marker: PhantomData<&'a ()>,
}

impl Paint {
    pub fn new() -> Result<Self, Error> {
        let raw = unsafe { sys::SkPaint_new() };
        NonNull::new(raw)
            .map(|raw| Self { raw })
            .ok_or(Error::NullReturn("SkPaint_new"))
    }

    pub fn as_ptr(&self) -> *mut sys::reskia_paint_t {
        self.raw.as_ptr()
    }

    pub fn set_stroke_width(&mut self, width: f32) {
        unsafe { sys::SkPaint_setStrokeWidth(self.raw.as_ptr(), width) };
    }

    pub fn stroke_width(&self) -> f32 {
        unsafe { sys::SkPaint_getStrokeWidth(self.raw.as_ptr()) }
    }

    pub fn set_argb(&mut self, a: u8, r: u8, g: u8, b: u8) {
        unsafe { sys::SkPaint_setARGB(self.raw.as_ptr(), a, r, g, b) };
    }

    pub fn from_handle_retained(handle: sys::sk_paint_t) -> Result<Self, Error> {
        let raw = unsafe { sys::reskia_paint_borrow_from_handle(handle) };
        let raw = NonNull::new(raw).ok_or(Error::NullReturn("Paint::from_handle_retained"))?;
        let retained = unsafe { sys::reskia_paint_retain(raw.as_ptr()) };
        let retained =
            NonNull::new(retained).ok_or(Error::NullReturn("Paint::from_handle_retained"))?;
        Ok(Self { raw: retained })
    }

    /// # Safety
    ///
    /// The returned borrow is tied to `'a` and must not outlive the underlying handle storage.
    pub unsafe fn borrow_from_handle<'a>(handle: sys::sk_paint_t) -> Option<BorrowedPaint<'a>> {
        NonNull::new(unsafe { sys::reskia_paint_borrow_from_handle(handle) }).map(|raw| {
            BorrowedPaint {
                raw,
                _marker: PhantomData,
            }
        })
    }
}

impl BorrowedPaint<'_> {
    pub fn as_ptr(&self) -> *mut sys::reskia_paint_t {
        self.raw.as_ptr()
    }
}

impl Clone for Paint {
    fn clone(&self) -> Self {
        let raw = unsafe { sys::reskia_paint_retain(self.raw.as_ptr()) };
        let raw = NonNull::new(raw).expect("reskia_paint_retain returned null");
        Self { raw }
    }
}

impl Drop for Paint {
    fn drop(&mut self) {
        unsafe { sys::reskia_paint_release(self.raw.as_ptr()) };
    }
}

pub struct Path {
    raw: NonNull<sys::reskia_path_t>,
}

pub struct BorrowedPath<'a> {
    raw: NonNull<sys::reskia_path_t>,
    _marker: PhantomData<&'a ()>,
}

impl Path {
    pub fn new() -> Result<Self, Error> {
        let raw = unsafe { sys::SkPath_new() };
        NonNull::new(raw)
            .map(|raw| Self { raw })
            .ok_or(Error::NullReturn("SkPath_new"))
    }

    pub fn as_ptr(&self) -> *mut sys::reskia_path_t {
        self.raw.as_ptr()
    }

    pub fn move_to(&mut self, x: f32, y: f32) {
        unsafe { sys::SkPath_moveTo(self.raw.as_ptr(), x, y) };
    }

    pub fn line_to(&mut self, x: f32, y: f32) {
        unsafe { sys::SkPath_lineTo(self.raw.as_ptr(), x, y) };
    }

    pub fn close(&mut self) {
        unsafe { sys::SkPath_close(self.raw.as_ptr()) };
    }

    pub fn is_empty(&self) -> bool {
        unsafe { sys::SkPath_isEmpty(self.raw.as_ptr()) }
    }

    pub fn count_points(&self) -> i32 {
        unsafe { sys::SkPath_countPoints(self.raw.as_ptr()) }
    }

    pub fn from_handle_retained(handle: sys::sk_path_t) -> Result<Self, Error> {
        let raw = unsafe { sys::reskia_path_borrow_from_handle(handle) };
        let raw = NonNull::new(raw).ok_or(Error::NullReturn("Path::from_handle_retained"))?;
        let retained = unsafe { sys::reskia_path_retain(raw.as_ptr()) };
        let retained =
            NonNull::new(retained).ok_or(Error::NullReturn("Path::from_handle_retained"))?;
        Ok(Self { raw: retained })
    }

    /// # Safety
    ///
    /// The returned borrow is tied to `'a` and must not outlive the underlying handle storage.
    pub unsafe fn borrow_from_handle<'a>(handle: sys::sk_path_t) -> Option<BorrowedPath<'a>> {
        NonNull::new(unsafe { sys::reskia_path_borrow_from_handle(handle) }).map(|raw| {
            BorrowedPath {
                raw,
                _marker: PhantomData,
            }
        })
    }

    pub fn interpolate_into(
        &self,
        ending: &Path,
        weight: f32,
        out_path: &mut Path,
    ) -> Result<(), Error> {
        let status = unsafe {
            sys::SkPath_interpolate(
                self.raw.as_ptr(),
                ending.raw.as_ptr(),
                weight,
                out_path.raw.as_ptr(),
            )
        };
        match status {
            sys::reskia_status_t::Ok => Ok(()),
            other => Err(Error::Status(other)),
        }
    }
}

impl BorrowedPath<'_> {
    pub fn as_ptr(&self) -> *mut sys::reskia_path_t {
        self.raw.as_ptr()
    }
}

impl Clone for Path {
    fn clone(&self) -> Self {
        let raw = unsafe { sys::reskia_path_retain(self.raw.as_ptr()) };
        let raw = NonNull::new(raw).expect("reskia_path_retain returned null");
        Self { raw }
    }
}

impl Drop for Path {
    fn drop(&mut self) {
        unsafe { sys::reskia_path_release(self.raw.as_ptr()) };
    }
}

pub fn render_demo_into_bgra(
    width: u32,
    height: u32,
    pixels: &mut [u32],
    time_seconds: f32,
) -> Result<(), Error> {
    if width == 0 || height == 0 {
        return Err(Error::OperationFailed("render_demo_into_bgra"));
    }
    let expected_len = width as usize * height as usize;
    if pixels.len() < expected_len {
        return Err(Error::OperationFailed(
            "render_demo_into_bgra: pixel buffer is too small",
        ));
    }

    let info_handle = unsafe { sys::SkImageInfo_MakeN32Premul(width as i32, height as i32) };
    let info_ptr = unsafe { sys::static_sk_image_info_get_ptr(info_handle) };
    let info_ptr = NonNull::new(info_ptr).ok_or(Error::NullReturn("SkImageInfo_MakeN32Premul"))?;

    let surface_handle = unsafe {
        sys::SkSurfaces_WrapPixels(
            info_ptr.as_ptr().cast::<sys::reskia_image_info_t>(),
            pixels.as_mut_ptr().cast(),
            (width as usize) * std::mem::size_of::<u32>(),
            std::ptr::null(),
        )
    };
    unsafe { sys::static_sk_image_info_delete(info_handle) };

    if surface_handle < 0 {
        return Err(Error::OperationFailed(
            "SkSurfaces_WrapPixels returned invalid handle",
        ));
    }

    let mut surface = Surface::from_handle_retained(surface_handle)?;
    let draw_result = (|| -> Result<(), Error> {
        let mut canvas = surface.borrow_canvas()?;
        canvas.clear_argb(0xFF, 0x12, 0x18, 0x24);

        let mut circle = Paint::new()?;
        circle.set_argb(0xFF, 0xF4, 0x7C, 0x2A);
        let radius = (width.min(height) as f32) * 0.18;
        let x = (width as f32) * (0.5 + 0.2 * time_seconds.cos());
        let y = (height as f32) * (0.5 + 0.2 * time_seconds.sin());
        canvas.draw_circle(x, y, radius, &circle);

        let mut triangle = Paint::new()?;
        triangle.set_argb(0xFF, 0x38, 0xB6, 0xFF);
        let mut path = Path::new()?;
        let w = width as f32;
        let h = height as f32;
        path.move_to(w * 0.15, h * 0.80);
        path.line_to(w * 0.50, h * 0.20);
        path.line_to(w * 0.85, h * 0.80);
        path.close();
        canvas.draw_path(&path, &triangle);
        Ok(())
    })();

    drop(surface);
    unsafe { sys::static_sk_surface_delete(surface_handle) };
    draw_result
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::ptr;

    fn create_raster_surface_handle(width: i32, height: i32) -> Result<sys::sk_surface_t, Error> {
        let info_handle = unsafe { sys::SkImageInfo_MakeN32Premul(width, height) };
        let info_ptr = unsafe { sys::static_sk_image_info_get_ptr(info_handle) };
        let info_ptr =
            NonNull::new(info_ptr).ok_or(Error::NullReturn("SkImageInfo_MakeN32Premul"))?;
        let surface_handle = unsafe {
            sys::SkSurfaces_RasterWithoutRowBytes(
                info_ptr.as_ptr().cast::<sys::reskia_image_info_t>(),
                ptr::null::<sys::reskia_surface_props_t>(),
            )
        };
        unsafe { sys::static_sk_image_info_delete(info_handle) };
        Ok(surface_handle)
    }

    #[test]
    fn from_raw_rejects_null_image() {
        let result = unsafe { Image::from_raw_owned(std::ptr::null_mut()) };
        assert!(matches!(
            result,
            Err(Error::NullReturn("Image::from_raw_owned"))
        ));
    }

    #[test]
    fn from_raw_rejects_null_surface() {
        let result = unsafe { Surface::from_raw_owned(std::ptr::null_mut()) };
        assert!(matches!(
            result,
            Err(Error::NullReturn("Surface::from_raw_owned"))
        ));
    }

    #[test]
    fn borrow_from_invalid_handles_returns_none() {
        assert!(unsafe { Image::borrow_from_handle(-1) }.is_none());
        assert!(unsafe { Surface::borrow_from_handle(-1) }.is_none());
        assert!(unsafe { Paint::borrow_from_handle(-1) }.is_none());
        assert!(unsafe { Path::borrow_from_handle(-1) }.is_none());
    }

    #[test]
    fn from_invalid_handles_returns_error() {
        assert!(matches!(
            Image::from_handle_retained(-1),
            Err(Error::NullReturn("Image::from_handle_retained"))
        ));
        assert!(matches!(
            Surface::from_handle_retained(-1),
            Err(Error::NullReturn("Surface::from_handle_retained"))
        ));
        assert!(matches!(
            Paint::from_handle_retained(-1),
            Err(Error::NullReturn("Paint::from_handle_retained"))
        ));
        assert!(matches!(
            Path::from_handle_retained(-1),
            Err(Error::NullReturn("Path::from_handle_retained"))
        ));
    }

    #[test]
    fn paint_and_path_basic_mutation() {
        let mut paint = Paint::new().expect("SkPaint_new should succeed");
        paint.set_stroke_width(3.0);
        paint.set_argb(255, 128, 64, 32);

        let mut path = Path::new().expect("SkPath_new should succeed");
        assert!(path.is_empty());
        path.move_to(0.0, 0.0);
        path.line_to(10.0, 10.0);
        path.close();
    }

    #[test]
    fn clone_keeps_paint_independent() {
        let mut original = Paint::new().expect("SkPaint_new should succeed");
        original.set_stroke_width(3.0);
        let mut cloned = original.clone();

        cloned.set_stroke_width(9.0);

        assert!((original.stroke_width() - 3.0).abs() < f32::EPSILON);
        assert!((cloned.stroke_width() - 9.0).abs() < f32::EPSILON);
    }

    #[test]
    fn clone_keeps_path_independent() {
        let mut original = Path::new().expect("SkPath_new should succeed");
        original.move_to(0.0, 0.0);
        original.line_to(1.0, 1.0);
        let mut cloned = original.clone();

        cloned.line_to(2.0, 2.0);

        assert_eq!(original.count_points(), 2);
        assert_eq!(cloned.count_points(), 3);
    }

    #[test]
    fn clone_drop_stress_for_paint_and_path() {
        for _ in 0..5000 {
            let mut paint = Paint::new().expect("SkPaint_new should succeed");
            paint.set_stroke_width(1.0);
            let mut paint_clone = paint.clone();
            paint_clone.set_stroke_width(2.0);
            drop(paint_clone);
            drop(paint);

            let mut path = Path::new().expect("SkPath_new should succeed");
            path.move_to(0.0, 0.0);
            path.line_to(1.0, 1.0);
            let mut path_clone = path.clone();
            path_clone.line_to(2.0, 2.0);
            path_clone.close();
            drop(path_clone);
            drop(path);
        }
    }

    #[test]
    fn surface_clone_drop_with_valid_instance() {
        let surface_handle =
            create_raster_surface_handle(32, 32).expect("surface handle should be created");
        let surface = Surface::from_handle_retained(surface_handle)
            .expect("surface from handle should succeed");
        let cloned = surface.clone();

        assert_eq!(surface.width(), 32);
        assert_eq!(cloned.height(), 32);

        drop(cloned);
        drop(surface);
        unsafe { sys::static_sk_surface_delete(surface_handle) };
    }

    #[test]
    fn image_clone_drop_with_snapshot_instance() {
        let surface_handle =
            create_raster_surface_handle(24, 24).expect("surface handle should be created");
        let surface = Surface::from_handle_retained(surface_handle)
            .expect("surface from handle should succeed");
        let image_handle = unsafe { sys::SkSurface_makeImageSnapshot(surface.as_ptr()) };
        let image = Image::from_handle_retained(image_handle)
            .expect("image snapshot should produce a valid image");
        let cloned = image.clone();

        assert_eq!(image.width(), 24);
        assert_eq!(image.height(), 24);
        assert_eq!(image.unique_id(), cloned.unique_id());

        drop(cloned);
        drop(image);
        drop(surface);
        unsafe {
            sys::static_sk_image_delete(image_handle);
            sys::static_sk_surface_delete(surface_handle);
        }
    }
}
