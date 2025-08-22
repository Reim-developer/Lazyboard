#![deny(clippy::pedantic, clippy::all, clippy::nursery, clippy::perf)]

pub mod utils {
    pub mod browser;
    pub mod fs_utils;
    pub mod memory;
}

pub mod core {
    pub mod r#macro;
    pub mod result_enum;
    pub mod sha;
    pub mod sqlite;
    pub mod time;
    pub mod utf8;
}

pub mod internal {
    pub mod app_config;
}

pub mod config {
    pub mod constant;
    pub mod toml;
}
