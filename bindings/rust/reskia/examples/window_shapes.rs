use std::num::NonZeroU32;
use std::rc::Rc;
use std::time::Instant;

use softbuffer::{Context, Surface};
use winit::dpi::PhysicalSize;
use winit::event::{Event, WindowEvent};
use winit::event_loop::EventLoop;
use winit::window::WindowBuilder;

fn nz(v: u32) -> NonZeroU32 {
    NonZeroU32::new(v.max(1)).expect("non-zero")
}

fn main() {
    if let Err(err) = run() {
        eprintln!("window sample failed: {err}");
        std::process::exit(1);
    }
}

fn run() -> Result<(), Box<dyn std::error::Error>> {
    let event_loop = EventLoop::new()?;
    let window = Rc::new(
        WindowBuilder::new()
            .with_title("Reskia Rust Window Sample")
            .with_inner_size(PhysicalSize::new(960, 640))
            .build(&event_loop)?,
    );

    let context = Context::new(window.clone())?;
    let mut surface = Surface::new(&context, window.clone())?;

    let mut size = window.inner_size();
    surface.resize(nz(size.width), nz(size.height))?;

    let start = Instant::now();

    event_loop.run(move |event, elwt| match event {
        Event::WindowEvent { event, .. } => match event {
            WindowEvent::CloseRequested => elwt.exit(),
            WindowEvent::Resized(new_size) => {
                size = new_size;
                if let Err(err) = surface.resize(nz(size.width), nz(size.height)) {
                    eprintln!("resize failed: {err}");
                    elwt.exit();
                }
            }
            WindowEvent::RedrawRequested => {
                if size.width == 0 || size.height == 0 {
                    return;
                }

                let mut buffer = match surface.buffer_mut() {
                    Ok(buffer) => buffer,
                    Err(err) => {
                        eprintln!("buffer_mut failed: {err}");
                        elwt.exit();
                        return;
                    }
                };

                let elapsed = start.elapsed().as_secs_f32();
                if let Err(err) =
                    reskia::render_demo_into_bgra(size.width, size.height, &mut buffer, elapsed)
                {
                    eprintln!("render failed: {err}");
                    elwt.exit();
                    return;
                }

                if let Err(err) = buffer.present() {
                    eprintln!("present failed: {err}");
                    elwt.exit();
                }
            }
            _ => {}
        },
        Event::AboutToWait => {
            window.request_redraw();
        }
        _ => {}
    })?;

    Ok(())
}
