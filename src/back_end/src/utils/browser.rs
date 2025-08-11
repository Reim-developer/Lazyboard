use std::ffi::{CStr, c_char};
use webbrowser::open;

/// # Safety
/// Be careful with raw pointers.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn open_browser(url: *const c_char) -> bool {
    unsafe {
        let Ok(c_str) = CStr::from_ptr(url).to_str() else {
            return false;
        };

        if c_str.is_empty() {
            return false;
        }

        open(c_str).is_ok()
    }
}
