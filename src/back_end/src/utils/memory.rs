use std::ffi::{CStr, CString, c_char};

pub(crate) const unsafe fn raw_from_ptr(url: *const c_char) -> (&'static str, bool) {
    unsafe {
        let Ok(c_str) = CStr::from_ptr(url).to_str() else {
            return ("", false);
        };

        (c_str, true)
    }
}

#[unsafe(no_mangle)]
/// # Safety
/// Careful with double free.
pub unsafe extern "C" fn raw_free_c_str(c_str: *const c_char) {
    unsafe {
        if !c_str.is_null() {
            let _ = CString::from_raw(c_str.cast_mut());
        }
    }
}
