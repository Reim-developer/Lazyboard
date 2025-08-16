use serde::{Deserialize, Serialize};

#[derive(Deserialize, Serialize)]
pub struct AppSettings {
    pub hide_when_closed: bool,
    pub notification: bool,
}

#[derive(Deserialize, Serialize)]
pub struct AppGuiSettings {
    pub background_color: String,
    pub foreground_color: String,
    pub background_button_color: String,
    pub foreground_button_color: String,
    pub background_table_header_color: String,
    pub foreground_table_header_color: String,
}

#[derive(Deserialize, Serialize)]
pub struct AppConfig {
    pub app_settings: AppSettings,
    pub app_gui_settings: AppGuiSettings,
}

impl AppConfig {
    #[must_use]
    pub fn default_config() -> Self {
        let app_settings = AppSettings {
            hide_when_closed: false,
            notification: false,
        };
        let app_gui_settings = AppGuiSettings {
            background_color: "#2f3136".to_string(),
            foreground_color: "#ffffff".to_string(),
            background_button_color: "#2f3136".to_string(),
            foreground_button_color: "#ffffff".to_string(),
            background_table_header_color: "#2f3136".to_string(),
            foreground_table_header_color: "#ffffff".to_string(),
        };

        Self {
            app_settings,
            app_gui_settings,
        }
    }
}
