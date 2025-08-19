#[test]
fn test_execute_sqlite() {
    use back_end::core::sqlite::{QueryResult, raw_execute_sql};
    use std::ffi::CString;

    unsafe {
        use QueryResult as R;

        let path = CString::new("test.db").unwrap();
        let path_c_str = path.as_ptr();

        let query = CString::new(
            r"
		CREATE TABLE IF NOT EXISTS test_table (
			name TEXT NOT NULL,
			age INTEGER PRIMARY KEY
		);
		",
        )
        .unwrap();
        let query_c_str = query.as_ptr();

        let status = raw_execute_sql(path_c_str, query_c_str);

        assert_ne!(status, R::C_STR_CONVERT_ERR);
        assert_ne!(status, R::EXECUTE_SQL_ERR);
        assert_ne!(status, R::OPEN_DATABASE_ERR);
        assert_eq!(status, R::OK);
    }
}
