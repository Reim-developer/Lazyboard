use std::ffi::c_char;
use webbrowser::open;

use crate::utils::memory::raw_from_ptr;

#[repr(C)]
pub enum OpenBrowserStatus {
    Ok,
    WrapRawCFailed,
    UrlIsEmpty,
    OpenBrowserFailed,
}

/// # Safety
/// Be careful with raw pointers.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn raw_open_browser(
    url: *const c_char,
) -> OpenBrowserStatus {
    unsafe {
        use OpenBrowserStatus as Status;

        let (c_str, is_ok) = raw_from_ptr(url);
        if !is_ok {
            return Status::WrapRawCFailed;
        }

        if c_str.is_empty() {
            return Status::UrlIsEmpty;
        }

        if open(c_str).is_ok() {
            Status::Ok
        } else {
            Status::OpenBrowserFailed
        }
    }
}
