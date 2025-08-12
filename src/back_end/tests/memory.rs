#[test]
fn test_memory_mod() {
    use back_end::utils::memory::raw_free_c_str;
    use std::ffi::CString;
    use std::ptr::null_mut;

    let raw_str = CString::new("Reim-developer")
        .map(CString::into_raw)
        .unwrap_or(null_mut());

    unsafe {
        raw_free_c_str(raw_str);
    }
}
