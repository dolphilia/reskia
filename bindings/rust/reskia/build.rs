use std::env;
use std::path::{Path, PathBuf};

fn main() {
    println!("cargo:rerun-if-env-changed=RESKIA_LIB_DIR");

    let crate_dir =
        PathBuf::from(env::var("CARGO_MANIFEST_DIR").expect("CARGO_MANIFEST_DIR is not set"));
    let repo_root = crate_dir
        .ancestors()
        .nth(3)
        .map(Path::to_path_buf)
        .expect("failed to resolve repository root from crate path");

    let explicit_dir = env::var("RESKIA_LIB_DIR").ok().map(PathBuf::from);
    let selected_dir = explicit_dir.or_else(|| default_lib_dir(&repo_root));

    if let Some(lib_dir) = selected_dir {
        let rpath = format!("-Wl,-rpath,{}", lib_dir.display());
        println!("cargo:rustc-link-arg={rpath}");
        println!("cargo:rustc-link-arg-examples={rpath}");
    }
}

fn default_lib_dir(repo_root: &Path) -> Option<PathBuf> {
    const CANDIDATES: &[&str] = &[
        "skia/cmake-build-local",
        "skia/cmake-build-debug",
        "skia/cmake-build-release",
        "skia/cmake-build-ci-prebuilt",
        "skia/cmake-build-codex-docrefresh-prebuilt",
        "skia/cmake-build-phase3-prebuilt",
        "skia/cmake-build-source-local",
        "skia/cmake-build-ci-source",
        "skia/cmake-build-codex-docrefresh-source",
        "skia/cmake-build-phase3-source",
    ];

    CANDIDATES
        .iter()
        .map(|relative| repo_root.join(relative))
        .find(|path| path.exists())
}
