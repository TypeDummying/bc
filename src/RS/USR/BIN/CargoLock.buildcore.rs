

pub fn cargo_lock_buildcore(paths: &Vec<&str>) {
    for path in paths {
        let mut lock_file = PathBuf::from(path);
        lock_file.push("Cargo.lock");
        if !lock_file.exists() {
            continue;
        }
        let lock_file = lock_file.to_str().unwrap();
        println!("cargo:rerun-if-changed={}", lock_file);
        let lock = cargo_lock::Lockfile::load(lock_file).unwrap();
        for package in lock.packages {
            let mut
        }
    }
}