use std::{ffi::{CStr}, os::raw::c_char, path::Path};

#[unsafe(no_mangle)]
pub unsafe extern "C" fn is_valid_path(path: *mut c_char) -> bool { unsafe {
    if path.is_null() {
        return false;
    }

    let c_str = match CStr::from_ptr(path).to_str() {
        Ok(string) => string,
        Err(_) => return false,
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
            .map(|raw| raw.into_raw())
            .unwrap_or(null_mut());

        assert_eq!(true, is_valid_path(c_string));
        free_c_str(c_string);
    }
}