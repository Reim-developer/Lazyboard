use std::ffi::{c_char, CString};

#[unsafe(no_mangle)]
pub unsafe extern "C" fn free_c_str(c_str: *mut c_char) { unsafe {
    if !c_str.is_null() {
        let _ = CString::from_raw(c_str);
    }
}}

#[test]
fn test_free_c_str() { unsafe {
    use std::ffi::CString;
    use std::ptr::null_mut;

    let raw_str = CString
        ::new("Reim-developer")
        .map(|raw| raw.into_raw())
        .unwrap_or(null_mut());

    free_c_str(raw_str);
}}