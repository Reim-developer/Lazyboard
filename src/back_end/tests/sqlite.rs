#[test]
fn test_add_text_clipboard() {
    use back_end::core::sqlite::{
        QueryResult, TextClipboard, add_text_clipboard, init_clipboard_cache,
    };
    use std::ffi::CString;
    use std::fs;

    use QueryResult as R;
    use TextClipboard as T;

    let content = CString::new("my clipboard content").unwrap();
    let content_hash = CString::new("my hash abc xyz ").unwrap();
    let content_type = CString::new("text").unwrap();
    let db_path = CString::new("test.db").unwrap();

    let _ = fs::remove_file(db_path.to_str().unwrap());

    let text_clipboard = T {
        content: content.as_ptr(),
        content_hash: content_hash.as_ptr(),
        content_type: content_type.as_ptr(),
        is_pinned: false,
    };

    unsafe {
        let init_result = init_clipboard_cache(db_path.as_ptr());
        let result = add_text_clipboard(db_path.as_ptr(), text_clipboard);

        assert_ne!(init_result, R::C_STR_CONVERT_ERR);
        assert_ne!(init_result, R::EXECUTE_SQL_ERR);
        assert_ne!(init_result, R::OPEN_DATABASE_ERR);
        assert_eq!(init_result, R::OK);

        assert_ne!(result, R::C_STR_CONVERT_ERR);
        assert_ne!(result, R::EXECUTE_SQL_ERR);
        assert_ne!(result, R::OPEN_DATABASE_ERR);
        assert_eq!(result, R::OK);
    }
}
