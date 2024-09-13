

use std::env;

fn main() {
    println!("cargo:rustc-link-search=native=C:/Users/VssAdministrator/.rustup/toolchains/stable-x86_64-pc-windows-msvc/lib/rustlib/x86_64-pc-windows-msvc/lib");
    println!("cargo:rustc-link-lib=static=atomic-64");
}
