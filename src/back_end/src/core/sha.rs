use std::ffi::{CStr, CString, c_char};

use sha2::{Digest, Sha256};

#[repr(C)]
#[allow(non_camel_case_types)]
pub enum GetShaResult {
    OK,
    C_STRING_CONVERT_ERR,
}

/// # Safety
/// Careful with raw pointers.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn text_sha256(
    text: *const c_char,
    out: *mut *mut c_char,
) -> GetShaResult {
    unsafe {
        use GetShaResult as R;

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
