use rusqlite::Connection;
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
		content_type TEXT NOT NULL,
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

        let is_err = sql.execute(INIT_QUERY, ()).is_err();

        if is_err {
            return R::EXECUTE_SQL_ERR;
        }

        R::OK
    }
}

#[repr(C)]
pub struct TextClipboard {
    pub content: *const c_char,
    pub content_hash: *const c_char,
    pub content_type: *const c_char,
    pub is_pinned: bool,
}

/// # Safety
/// Careful with raw pointers & memory leaks.
#[must_use]
#[unsafe(no_mangle)]
pub unsafe extern "C" fn raw_add_text_clipboard(
    db_path: *const c_char,
    text_clipboard: TextClipboard,
) -> QueryResult {
    use QueryResult as R;

    unsafe {
        let Ok(file_path_cstr) = CStr::from_ptr(db_path).to_str() else {
            return R::C_STR_CONVERT_ERR;
        };

        let Ok(sql) = Connection::open(file_path_cstr) else {
            return R::OPEN_DATABASE_ERR;
        };

        let Ok(content_str) = CStr::from_ptr(text_clipboard.content).to_str()
        else {
            return R::C_STR_CONVERT_ERR;
        };

        let Ok(content_hash_str) =
            CStr::from_ptr(text_clipboard.content_hash).to_str()
        else {
            return R::C_STR_CONVERT_ERR;
        };

        let Ok(content_type_str) =
            CStr::from_ptr(text_clipboard.content_type).to_str()
        else {
            return R::C_STR_CONVERT_ERR;
        };

        let query = r"
            INSERT INTO clipboard_cache (content, content_hash, content_type, is_pinned)
            VALUES (?, ?, ?, ?)
        ";

        let binds = (
            content_str,
            content_hash_str,
            content_type_str,
            text_clipboard.is_pinned,
        );
        let is_err = sql.execute(query, binds).is_err();

        /* For panic testing only. Don't remove it. */
        /* sql.execute(query, binds).unwrap(); */

        if is_err {
            return R::EXECUTE_SQL_ERR;
        }

        R::OK
    }
}
