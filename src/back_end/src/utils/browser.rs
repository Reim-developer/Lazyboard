use std::ffi::{CStr, c_char};
use webbrowser::open;

use crate::core::result_enum::ResultContext;

/// # Safety
/// Be careful with raw pointers.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn open_browser(url: *const c_char) -> ResultContext {
    unsafe {
        use ResultContext as R;

        let c_str = CStr::from_ptr(url).to_string_lossy();

        let is_ok = open(&c_str).is_ok();

        if !is_ok {
            return R::FAILED;
        }

        R::OK
    }
}
