use crate::internal::app_config::AppConfig;
use crate::utils::memory::raw_from_ptr;
use std::ffi::{CString, c_char};
use std::fs::{self, File};
use std::io::Write;
use std::path::Path;
use std::ptr::null_mut;

const APP_NAME: &str = "Lazyboard";

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
pub unsafe extern "C" fn raw_new_folder(
    folder_path: *const c_char,
) -> CreateFileSystemStatus {
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

#[repr(C)]
pub enum WriteConfigStatus {
    Ok,
    TomlToStringFailed,
    CreateDirFailed,
    CreateFileFailed,
    WriteFileFailed,
    GetDataLocalFailed,
}

#[must_use]
#[unsafe(no_mangle)]
pub extern "C" fn raw_config_dir() -> *mut c_char {
    let result = dirs::config_dir()
        .and_then(|path| path.into_os_string().into_string().ok())
        .and_then(|string| CString::new(string).ok());

    result.map_or(null_mut(), CString::into_raw)
}

#[must_use]
#[unsafe(no_mangle)]
pub extern "C" fn raw_cache_dir() -> *mut c_char {
    let result = dirs::cache_dir()
        .and_then(|path| path.into_os_string().into_string().ok())
        .and_then(|string| CString::new(string).ok());

    result.map_or(null_mut(), CString::into_raw)
}

#[must_use]
#[unsafe(no_mangle)]
pub extern "C" fn raw_write_default_config() -> WriteConfigStatus {
    use WriteConfigStatus as Status;

    let app_config = AppConfig::default_config();

    let Ok(toml_string) = toml::to_string(&app_config) else {
        return Status::TomlToStringFailed;
    };

    if let Some(data_local) = dirs::config_dir() {
        let config_dir_string = data_local.to_string_lossy().to_string();

        let config_dir = format!("{config_dir_string}/{APP_NAME}");
        if fs::create_dir_all(&config_dir).is_err() {
            return Status::CreateDirFailed;
        }

        let config_file_path = format!("{config_dir}/settings.toml");
        let path = Path::new(&config_file_path);

        if !path.exists() {
            let Ok(mut file) = File::create_new(config_file_path) else {
                return Status::CreateFileFailed;
            };

            match file.write_all(toml_string.as_bytes()) {
                Ok(()) => return Status::Ok,
                Err(_) => return Status::WriteFileFailed,
            };
        }

        return Status::Ok;
    }

    Status::GetDataLocalFailed
}
