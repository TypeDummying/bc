

pub fn compile_core_files() {
    println!("cargo:rerun-if-changed=src/RS/USR/LIB/libc/src");
    println!("cargo:rerun-if-changed=src/RS/USR/LIB/libm/src");
    println!("cargo:rerun-if-changed=src/RS/USR/LIB/libcore/src");
    println!("cargo:rerun-if-changed=src/RS/USR/LIB/liballoc/src");
    println!("cargo:rerun-if-changed=src/RS/USR/LIB/librs_kernel/src");

    let out_dir = env::var("OUT_DIR").unwrap();
    let profile = env::var("PROFILE").unwrap();
    let target_arch = env::var("TARGET_ARCH
