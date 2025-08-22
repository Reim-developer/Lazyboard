use crate::core::result_enum::ResultContext;
use crate::ensure;
use crate::internal::app_config::AppConfig;
use std::ffi::{CStr, CString, c_char};
use std::fs::{self, File};
use std::io::Write;
use std::path::Path;

const APP_NAME: &str = "Lazyboard";

/// # Safety
/// Be careful with raw pointers.
#[must_use]
#[unsafe(no_mangle)]
pub unsafe extern "C" fn new_folder(
    folder_path: *const c_char,
) -> ResultContext {
    unsafe {
        use ResultContext as R;
        let folder_path_str = CStr::from_ptr(folder_path).to_string_lossy();

        let is_ok = fs::create_dir_all(&*folder_path_str).is_ok();
        if !is_ok {
            return R::FAILED;
        }

        R::OK
    }
}

#[must_use]
#[unsafe(no_mangle)]
/// # Safety
/// Careful with raw pointers.
pub unsafe extern "C" fn path_exists(path: *const c_char) -> bool {
    unsafe {
        let path_str = CStr::from_ptr(path).to_string_lossy();

        Path::new(&*path_str).exists()
    }
}

#[repr(C)]
#[allow(non_camel_case_types)]
pub enum ConfigResult {
    OK,
    TOML_TO_STRING_ERR,
    CREATE_DIR_ERR,
    CREATE_FILE_ERR,
    WRITE_FILE_ERR,
    GET_CONFIG_DIR_ERR,
}

#[derive(PartialEq, Eq, Debug)]
#[repr(C)]
#[allow(non_camel_case_types)]
pub enum UtilsResult {
    OK,
    ALLOC_ERR,
    NULL_DEFERENCE_ERR,
    GET_DIR_ERR,
}

#[must_use]
#[unsafe(no_mangle)]
/// # Safety
/// Careful with memory leaks & double-free.
pub unsafe extern "C" fn config_dir(out: *mut *mut c_char) -> UtilsResult {
    use UtilsResult as R;

    unsafe {
        if let Some(config_path) = dirs::config_dir() {
            let path = config_path.to_string_lossy();

            let Ok(config_path_cstring) = CString::new(path.to_string()) else {
                return R::ALLOC_ERR;
            };

            ensure!(!out.is_null(), R::NULL_DEFERENCE_ERR);
            *out = config_path_cstring.into_raw();

            return R::OK;
        }

        R::GET_DIR_ERR
    }
}

#[must_use]
#[unsafe(no_mangle)]
/// # Safety
/// Careful with raw pointers & memory leaks
pub unsafe extern "C" fn cache_dir(out: *mut *mut c_char) -> UtilsResult {
    use UtilsResult as R;

    unsafe {
        if let Some(result) = dirs::cache_dir() {
            let path_str = result.to_string_lossy();

            let Ok(path_c_string) = CString::new(path_str.to_string()) else {
                return R::ALLOC_ERR;
            };

            ensure!(!out.is_null(), R::NULL_DEFERENCE_ERR);
            *out = path_c_string.into_raw();

            return R::OK;
        }

        R::GET_DIR_ERR
    }
}

#[must_use]
#[unsafe(no_mangle)]
pub extern "C" fn create_default_cfg() -> ConfigResult {
    use ConfigResult as R;

    let app_config = AppConfig::default_config();

    let Ok(toml_string) = toml::to_string(&app_config) else {
        return R::TOML_TO_STRING_ERR;
    };

    if let Some(data_local) = dirs::config_dir() {
        let config_dir_string = data_local.to_string_lossy().to_string();

        let config_dir = format!("{config_dir_string}/{APP_NAME}");
        if fs::create_dir_all(&config_dir).is_err() {
            return R::CREATE_DIR_ERR;
        }

        let config_file_path = format!("{config_dir}/settings.toml");
        let path = Path::new(&config_file_path);

        if !path.exists() {
            let Ok(mut file) = File::create_new(config_file_path) else {
                return R::CREATE_FILE_ERR;
            };

            match file.write_all(toml_string.as_bytes()) {
                Ok(()) => return R::OK,
                Err(_) => return R::WRITE_FILE_ERR,
            };
        }

        return R::OK;
    }

    R::GET_CONFIG_DIR_ERR
}
