use crate::config::constant::{
    APP_GUI_SETTINGS, APP_SETTINGS, BACKGROUND_COLOR, BACKGROUND_COLOR_BUTTON,
    BACKGROUND_COLOR_TABLE_HEADER, FALLBACK_BG_BUTTON_COLOR, FALLBACK_BG_COLOR,
    FALLBACK_BG_TABLE_HEADER_COLOR, FALLBACK_FG_BUTTON_COLOR,
    FALLBACK_FG_COLOR, FALLBACK_FG_TABLE_HEADER_COLOR, FOREGROUND_COLOR,
    FOREGROUND_COLOR_BUTTON, FOREGROUND_COLOR_TABLE_HEADER, HIDE_WHEN_CLOSED,
    HIDE_WHEN_CLOSED_FALLBACK, NOTIFICATION, NOTIFICATION_FALLBACK,
};
use std::{
    ffi::{CStr, CString, c_char},
    fs,
};
use toml::Value;

#[repr(C)]
pub struct AppSettings {
    pub hide_when_closed: bool,
    pub notification: bool,
}

#[repr(C)]
pub struct AppGuiSettings {
    pub background_color: *mut c_char,
    pub foreground_color: *mut c_char,
    pub background_button_color: *mut c_char,
    pub foreground_button_color: *mut c_char,
    pub background_header_table_color: *mut c_char,
    pub foreground_header_table_color: *mut c_char,
}

#[repr(C)]
pub struct AppConfig {
    pub app_settings: AppSettings,
    pub app_gui_settings: AppGuiSettings,
}

#[repr(C)]
pub enum ReadConfigResult {
    Ok,
    ReadFileFailed,
    Utf8Error,
    ParseTomlFailed,
    ConvertToMutFailed,
    ConvertToCStringFailed,
}

fn color_by_settings(
    toml_value: &Value,
    field_name: &str,
    fallback: &str,
) -> String {
    let color = toml_value
        .get(APP_GUI_SETTINGS)
        .and_then(|value| value.get(field_name))
        .and_then(Value::as_str)
        .unwrap_or(fallback);

    color.to_string()
}

fn app_settings(toml_value: &Value) -> AppSettings {
    AppSettings {
        hide_when_closed: toml_value
            .get(APP_SETTINGS)
            .and_then(|value| value.get(HIDE_WHEN_CLOSED))
            .and_then(Value::as_bool)
            .unwrap_or(HIDE_WHEN_CLOSED_FALLBACK),

        notification: toml_value
            .get(APP_SETTINGS)
            .and_then(|value| value.get(NOTIFICATION))
            .and_then(Value::as_bool)
            .unwrap_or(NOTIFICATION_FALLBACK),
    }
}

/// # Safety
/// Careful with raw pointers.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn read_exists_config(
    file_path: *const c_char,
    out: *mut AppConfig,
) -> ReadConfigResult {
    use ReadConfigResult as Status;

    let file_path_str = unsafe { CStr::from_ptr(file_path).to_str() };
    let Ok(file_path) = file_path_str else {
        return Status::Utf8Error;
    };

    let Ok(result) = fs::read_to_string(file_path) else {
        return Status::ReadFileFailed;
    };

    let Ok(toml_value) = toml::from_str::<Value>(&result) else {
        return Status::ParseTomlFailed;
    };

    let app_settings = app_settings(&toml_value);

    let bg_color =
        color_by_settings(&toml_value, BACKGROUND_COLOR, FALLBACK_BG_COLOR);
    let fg_color =
        color_by_settings(&toml_value, FOREGROUND_COLOR, FALLBACK_FG_COLOR);
    let bg_button_color = color_by_settings(
        &toml_value,
        BACKGROUND_COLOR_BUTTON,
        FALLBACK_BG_BUTTON_COLOR,
    );
    let fg_button_color = color_by_settings(
        &toml_value,
        FOREGROUND_COLOR_BUTTON,
        FALLBACK_FG_BUTTON_COLOR,
    );
    let bg_table_header_color = color_by_settings(
        &toml_value,
        BACKGROUND_COLOR_TABLE_HEADER,
        FALLBACK_BG_TABLE_HEADER_COLOR,
    );
    let fg_table_header_color = color_by_settings(
        &toml_value,
        FOREGROUND_COLOR_TABLE_HEADER,
        FALLBACK_FG_TABLE_HEADER_COLOR,
    );

    let Ok(bg_cstr) = CString::new(bg_color) else {
        return Status::ConvertToCStringFailed;
    };

    let Ok(fg_cstr) = CString::new(fg_color) else {
        return Status::ConvertToCStringFailed;
    };

    let Ok(bg_btn_cstr) = CString::new(bg_button_color) else {
        return Status::ConvertToCStringFailed;
    };

    let Ok(fg_btn_cstr) = CString::new(fg_button_color) else {
        return Status::ConvertToCStringFailed;
    };

    let Ok(bg_table_header_cstr) = CString::new(bg_table_header_color) else {
        return Status::ConvertToCStringFailed;
    };

    let Ok(fg_table_header_cstr) = CString::new(fg_table_header_color) else {
        return Status::ConvertToCStringFailed;
    };

    if let Some(config) = unsafe { out.as_mut() } {
        config.app_settings.hide_when_closed = app_settings.hide_when_closed;
        config.app_settings.notification = app_settings.notification;
        config.app_gui_settings.background_color = bg_cstr.into_raw();
        config.app_gui_settings.foreground_color = fg_cstr.into_raw();
        config.app_gui_settings.background_button_color =
            bg_btn_cstr.into_raw();
        config.app_gui_settings.foreground_button_color =
            fg_btn_cstr.into_raw();
        config.app_gui_settings.background_header_table_color =
            bg_table_header_cstr.into_raw();
        config.app_gui_settings.foreground_header_table_color =
            fg_table_header_cstr.into_raw();

        return ReadConfigResult::Ok;
    }

    ReadConfigResult::ConvertToMutFailed
}

#[unsafe(no_mangle)]
/// # Safety
/// Be careful with raw pointers & double-free.
pub unsafe extern "C" fn free_app_config(config: *mut AppConfig) {
    unsafe {
        if let Some(cfg) = config.as_mut() {
            let _ = CString::from_raw(cfg.app_gui_settings.background_color);
            let _ = CString::from_raw(cfg.app_gui_settings.foreground_color);
            let _ =
                CString::from_raw(cfg.app_gui_settings.background_button_color);
            let _ =
                CString::from_raw(cfg.app_gui_settings.foreground_button_color);
            let _ = CString::from_raw(
                cfg.app_gui_settings.background_header_table_color,
            );
            let _ = CString::from_raw(
                cfg.app_gui_settings.foreground_header_table_color,
            );
        }
    }
}
