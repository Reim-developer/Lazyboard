#[test]
fn test_raw_cache_dir() {
    use back_end::utils::fs_utils::UtilsResult;
    use back_end::utils::fs_utils::cache_dir;
    use std::ffi::CString;
    use std::ffi::c_char;
    use std::ptr::null_mut;

    use UtilsResult as R;
    unsafe {
        let mut out: *mut c_char = null_mut();
        let result = cache_dir(&raw mut out);

        let out_c_string = CString::from_raw(out);
        let out_str = out_c_string.to_string_lossy();

        assert_ne!(result, R::ALLOC_ERR);
        assert_ne!(result, R::NULL_DEFERENCE_ERR);
        assert_ne!(result, R::GET_DIR_ERR);
        assert_eq!(result, R::OK);
        assert!(!out_str.is_empty());
    }
}
