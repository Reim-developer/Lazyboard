#[test]
fn test_config() {
    use back_end::utils::fs_utils::raw_local_data;
    use back_end::utils::memory::raw_free_c_str;

    let c_str = raw_local_data();
    assert!(!c_str.is_null());

    unsafe {
        raw_free_c_str(c_str);
    }
}
