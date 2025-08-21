use std::ffi::{CStr, CString, c_char};

use crate::core::result_enum::AllocResult;
use crate::ensure;
use sha2::{Digest, Sha256};

/// # Safety
/// Careful with raw pointers.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn text_sha256(
    text: *const c_char,
    out: *mut *mut c_char,
) -> AllocResult {
    unsafe {
        use AllocResult as R;

        ensure!(!text.is_null(), R::NULL_DEFERENCE_ERR);
        ensure!(!out.is_null(), R::NULL_DEFERENCE_ERR);

        let mut hasher = Sha256::new();

        let text_bytes = CStr::from_ptr(text).to_bytes();
        hasher.update(text_bytes);
        let result = hasher.finalize();

        let to_hex = hex::encode(result);

        let Ok(result_c_char) = CString::new(to_hex) else {
            return R::C_STRING_CONVERT_ERR;
        };

        *out = result_c_char.into_raw();

        R::OK
    }
}
