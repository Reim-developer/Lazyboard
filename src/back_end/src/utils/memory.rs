use std::ffi::{CString, c_char};

#[unsafe(no_mangle)]
/// # Safety
/// Careful with double free.
pub unsafe extern "C" fn free_alloc(c_str: *mut c_char) {
    unsafe {
        if !c_str.is_null() {
            let _ = CString::from_raw(c_str);
        }
    }
}
