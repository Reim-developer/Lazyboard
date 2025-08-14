use std::{
    ffi::{CStr, CString, c_char},
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

const FALLBACK_BG_COLOR: &str = "#2f3136";
const FALLBACK_FG_COLOR: &str = "#ffffff";

/// # Safety
/// Careful with raw pointers.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn raw_exists_config(
    raw_file_path: *const c_char,
    raw_cfg_out: *mut RawAppConfig,
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

    let bg_color = toml_value
        .get("app_gui_settings")
        .and_then(|value| value.get("background_color"))
        .and_then(Value::as_str)
        .unwrap_or(FALLBACK_BG_COLOR);

    let fg_color = toml_value
        .get("app_gui_settings")
        .and_then(|value| value.get("foreground_color"))
        .and_then(Value::as_str)
        .unwrap_or(FALLBACK_FG_COLOR);

    let Ok(bg_cstr) = CString::new(bg_color) else {
        return Status::ParseTomlFailed;
    };

    let Ok(fg_cstr) = CString::new(fg_color) else {
        return Status::ParseTomlFailed;
    };

    if let Some(config) = unsafe { raw_cfg_out.as_mut() } {
        config.app_settings.hide_when_closed = app_settings.hide_when_closed;
        config.app_settings.notification = app_settings.notification;
        config.app_gui_settings.background_color = bg_cstr.into_raw();
        config.app_gui_settings.foreground_color = fg_cstr.into_raw();

        return RawReadAppConfigStatus::Ok;
    }

    RawReadAppConfigStatus::ConvertToMutFailed
}

#[unsafe(no_mangle)]
/// # Safety
/// Be careful with raw pointers & double-free.
pub unsafe extern "C" fn raw_free_cstr_app_config(config: *mut RawAppConfig) {
    unsafe {
        if let Some(cfg) = config.as_mut() {
            let _ = CString::from_raw(cfg.app_gui_settings.background_color);
            let _ = CString::from_raw(cfg.app_gui_settings.foreground_color);
        }
    }
}
