

use std::path::PathBuf;

use crate::domain::path::get_native_project_paths;

pub fn get_native_projects() -> Vec<PathBuf> {
    get_native_project_paths()
}
