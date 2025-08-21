use std::ffi::{CStr, CString, c_char};

use crate::{core::result_enum::AllocResult, ensure};

#[unsafe(no_mangle)]
/// # Safety
/// Careful with raw pointers & memory leaks
pub unsafe extern "C" fn to_utf8(
    content: *const c_char,
    out: *mut *mut c_char,
) -> AllocResult {
    use AllocResult as R;

    unsafe {
        ensure!(!content.is_null(), R::NULL_DEFERENCE_ERR);
        ensure!(!content.is_null(), R::NULL_DEFERENCE_ERR);

        let result_str = CStr::from_ptr(content).to_string_lossy();

        let Ok(c_str) = CString::new(result_str.as_ref()) else {
            return R::C_STRING_CONVERT_ERR;
        };

        *out = c_str.into_raw();

        R::OK
    }
}
