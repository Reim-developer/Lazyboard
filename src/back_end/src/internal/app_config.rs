use serde::{Deserialize, Serialize};

#[derive(Deserialize, Serialize)]
pub struct AppSettings {
    pub hide_when_closed: bool,
    pub notification: bool,
}

#[derive(Deserialize, Serialize)]
pub struct AppConfig {
    pub app_settings: AppSettings,
}

#[must_use]
pub const fn get_default_config() -> AppConfig {
    let settings = AppSettings {
        hide_when_closed: false,
        notification: false,
    };

    AppConfig {
        app_settings: settings,
    }
}
