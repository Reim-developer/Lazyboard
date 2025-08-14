use std::{
    ffi::{CStr, c_char},
    fs,
};
use toml::Value;

#[repr(C)]
pub struct RawAppSettings {
    pub hide_when_closed: bool,
    pub notification: bool,
}

#[repr(C)]
pub struct RawAppGuiSettings {
    pub background_color: *mut c_char,
    pub foreground_color: *mut c_char,
}

#[repr(C)]
pub struct RawAppConfig {
    pub app_settings: RawAppSettings,
    pub app_gui_settings: RawAppGuiSettings,
}

#[repr(C)]
pub enum RawReadAppConfigStatus {
    Ok,
    ReadFileFailed,
    Utf8Error,
    ParseTomlFailed,
    ConvertToMutFailed,
}

/// # Safety
/// Careful with raw pointers.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn raw_exists_config(
    raw_file_path: *const c_char,
    raw_cfg_out: *mut RawAppSettings,
) -> RawReadAppConfigStatus {
    use RawReadAppConfigStatus as Status;

    let file_path_str = unsafe { CStr::from_ptr(raw_file_path).to_str() };
    let Ok(file_path) = file_path_str else {
        return Status::Utf8Error;
    };

    let Ok(result) = fs::read_to_string(file_path) else {
        return Status::ReadFileFailed;
    };

    let Ok(toml_value) = toml::from_str::<Value>(&result) else {
        return Status::ParseTomlFailed;
    };

    let app_settings = RawAppSettings {
        hide_when_closed: toml_value
            .get("app_settings")
            .and_then(|value| value.get("hide_when_closed"))
            .and_then(Value::as_bool)
            .unwrap_or(false),

        notification: toml_value
            .get("app_settings")
            .and_then(|value| value.get("notification"))
            .and_then(Value::as_bool)
            .unwrap_or(false),
    };

    if let Some(config) = unsafe { raw_cfg_out.as_mut() } {
        config.hide_when_closed = app_settings.hide_when_closed;
        config.notification = app_settings.notification;

        return RawReadAppConfigStatus::Ok;
    }

    RawReadAppConfigStatus::ConvertToMutFailed
}
