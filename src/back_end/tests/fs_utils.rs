#[test]
fn test_raw_cache_dir() {
    use back_end::utils::fs_utils::raw_cache_dir;
    use std::ffi::CStr;

    unsafe {
        let result = raw_cache_dir();
        let result_str = CStr::from_ptr(result).to_string_lossy();

        assert!(!result.is_null());
        assert!(!result_str.is_empty());
    }
}
