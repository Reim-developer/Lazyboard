#[test]
fn test_time_null_deference() {
    unsafe {
        use back_end::core::{result_enum::AllocResult, time::time_now};
        use std::ffi::c_char;
        use std::ptr::null_mut;

        use AllocResult as R;

        let out: *mut *mut c_char = null_mut();
        let result = time_now(out);

        assert_ne!(result, R::OK);
        assert_ne!(result, R::C_STRING_CONVERT_ERR);
        assert_eq!(result, R::NULL_DEFERENCE_ERR);
    }
}

#[test]
fn test_time_now() {
    unsafe {
        use back_end::core::{result_enum::AllocResult, time::time_now};
        use std::ffi::{CString, c_char};
        use std::ptr::null_mut;

        use AllocResult as R;

        let mut out: *mut c_char = null_mut();
        let result = time_now(&raw mut out);

        let out_str = CString::from_raw(out);
        let to_str = out_str.to_string_lossy();

        assert_ne!(result, R::C_STRING_CONVERT_ERR);
        assert_ne!(result, R::NULL_DEFERENCE_ERR);
        assert_eq!(result, R::OK);
        assert!(!to_str.is_empty());
    }
}
