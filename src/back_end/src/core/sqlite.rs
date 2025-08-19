use sqlite::Connection;
use std::ffi::{CStr, c_char};

#[derive(PartialEq, Eq, Debug)]
#[repr(C)]
#[allow(non_camel_case_types)]
pub enum QueryResult {
    OK,
    OPEN_DATABASE_ERR,
    C_STR_CONVERT_ERR,
    EXECUTE_SQL_ERR,
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
) -> QueryResult {
    unsafe {
        use QueryResult as R;

        let Ok(file_path_cstr) = CStr::from_ptr(file_path).to_str() else {
            return R::C_STR_CONVERT_ERR;
        };

        let Ok(sql) = Connection::open(file_path_cstr) else {
            return R::OPEN_DATABASE_ERR;
        };

        let is_err = sql.execute(INIT_QUERY).is_err();

        if is_err {
            return R::EXECUTE_SQL_ERR;
        }

        R::OK
    }
}

/// # Safety
/// Careful with raw pointers & memory leaks.
#[must_use]
#[unsafe(no_mangle)]
pub unsafe extern "C" fn raw_execute_sql(
    db_path: *const c_char,
    query: *const c_char,
) -> QueryResult {
    use QueryResult as R;
    unsafe {
        let Ok(file_path_cstr) = CStr::from_ptr(db_path).to_str() else {
            return R::C_STR_CONVERT_ERR;
        };

        let Ok(sql) = Connection::open(file_path_cstr) else {
            return R::OPEN_DATABASE_ERR;
        };

        let Ok(query_str) = CStr::from_ptr(query).to_str() else {
            return R::C_STR_CONVERT_ERR;
        };

        let is_err = sql.execute(query_str).is_err();

        if is_err {
            return R::EXECUTE_SQL_ERR;
        }

        R::OK
    }
}
