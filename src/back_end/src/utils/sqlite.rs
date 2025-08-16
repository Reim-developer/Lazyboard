use sqlite::Connection;
use std::ffi::{CStr, c_char};

#[repr(C)]
pub enum InitDatabaseStatus {
    Ok,
    CreateDatabaseFailed,
    CStrConvertFailed,
    ExecuteSqlFailed,
}

const INIT_QUERY: &str = r"--sql
	CREATE TABLE IF NOT EXISTS clipboard_cache (
		id INTEGER PRIMARY KEY AUTOINCREMENT,
		content_hash TEXT NOT NULL UNIQUE,
		time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
		content TEXT NOT NULL,
		type TEXT NOT NULL,
		is_pinned BOOLEAN NOT NULL DEFAULT FALSE
	);
";

#[unsafe(no_mangle)]
/// # Safety
/// Careful with unsafe context & raw pointers.
pub unsafe extern "C" fn raw_init_clipboard_cache(
    file_path: *const c_char,
) -> InitDatabaseStatus {
    unsafe {
        use InitDatabaseStatus as Status;

        let Ok(file_path_cstr) = CStr::from_ptr(file_path).to_str() else {
            return Status::CStrConvertFailed;
        };

        let Ok(sql) = Connection::open(file_path_cstr) else {
            return Status::CreateDatabaseFailed;
        };

        let is_err = sql.execute(INIT_QUERY).is_err();

        if is_err {
            return Status::ExecuteSqlFailed;
        }

        Status::Ok
    }
}
