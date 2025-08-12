use crate::utils::memory::raw_from_ptr;
use std::ffi::c_char;
use std::fs;
use std::path::Path;

#[repr(C)]
pub enum CreateFileSystemStatus {
    Ok,
    WrapRawCFailed,
    Failed,
}

/// # Safety
/// Be careful with raw pointers.
#[must_use]
#[unsafe(no_mangle)]
pub unsafe extern "C" fn raw_new_folder(folder_path: *const c_char) -> CreateFileSystemStatus {
    unsafe {
        use CreateFileSystemStatus as Status;
        let (c_str, is_ok) = raw_from_ptr(folder_path);

        if !is_ok {
            return Status::WrapRawCFailed;
        }

        let is_create_success = fs::create_dir_all(c_str).is_ok();
        if !is_create_success {
            return Status::Failed;
        }

        Status::Ok
    }
}

#[must_use]
#[unsafe(no_mangle)]
/// # Safety
/// Careful with raw pointers.
pub unsafe extern "C" fn raw_is_path_exists(path: *const c_char) -> bool {
    unsafe {
        let (c_str, is_ok) = raw_from_ptr(path);
        if !is_ok {
            return false;
        }

        Path::new(c_str).exists()
    }
}
