use std::ffi::{CString, c_schar};

use chrono::{DateTime, Utc};

use crate::{core::result_enum::AllocResult, ensure};

/// # Safety
/// Careful with raw pointers and memory leaks.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn time_now(out: *mut *mut c_schar) -> AllocResult {
    unsafe {
        use AllocResult as R;

        ensure!(!out.is_null(), R::NULL_DEFERENCE_ERR);

        let now_utc: DateTime<Utc> = Utc::now();
        let fmt_utc = now_utc.format("%Y-%m-%d %H:%M:%S").to_string();

        let Ok(fmt_utc_cstr) = CString::new(fmt_utc) else {
            return R::C_STRING_CONVERT_ERR;
        };

        *out = fmt_utc_cstr.into_raw();

        R::OK
    }
}
