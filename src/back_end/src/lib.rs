#![deny(clippy::pedantic, clippy::all, clippy::nursery, clippy::perf)]

pub mod utils {
    pub mod browser;
    pub mod fs_utils;
    pub mod memory;
}

pub mod core {
    pub mod sqlite;
}

pub mod internal {
    pub mod app_config;
}

pub mod raw_config {
    pub mod constant;
    pub mod raw_toml;
}
