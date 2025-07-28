use std::{ffi::{CStr}, os::raw::c_char, path::Path};

#[unsafe(no_mangle)]
/// # Safety
/// 
/// Make sure this `path` value given to 
/// function parameter is a valid UTF-8 string.
pub unsafe extern "C" fn is_valid_path(path: *mut c_char) -> bool { unsafe {
    if path.is_null() {
        return false;
    }
    
    let Ok(c_str) = CStr::from_ptr(path).to_str() 
    else { 
        return false 
    };

    if c_str.is_empty() {
        return false;
    }

    let path = Path::new(c_str);

    path
        .as_os_str()
        .as_encoded_bytes()
        .iter()
        .all(|&char| char != 0)
}}

#[test]
fn test_is_valid_path() {
    use std::ffi::{CString};
    use std::ptr::null_mut;
    use crate::alloc::memory::free_c_str;

    unsafe {
        let c_string = CString
            ::new("../../src/utils/path.rs") /* Path to some exits file ...*/
            .map(CString::into_raw)
            .unwrap_or(null_mut());

        assert!(is_valid_path(c_string));
        free_c_str(c_string);
    }
}