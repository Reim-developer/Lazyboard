#[test]
/* Null deference beavior test. */
fn test_utf8_null_dererence() {
    use back_end::core::result_enum::AllocResult;
    use back_end::core::utf8::to_utf8;
    use std::ffi::c_char;
    use std::ptr;

    use AllocResult as R;

    unsafe {
        let mut output_null: *mut c_char = ptr::null_mut();
        let result_null: *const c_char = ptr::null();

        let result = to_utf8(result_null, &raw mut output_null);

        assert_ne!(result, R::OK);
        assert_ne!(result, R::C_STRING_CONVERT_ERR);
        assert_eq!(result, R::NULL_DEFERENCE_ERR);
    }
}

#[test]
fn test_utf8() {
    unsafe {
        use back_end::core::result_enum::AllocResult;
        use back_end::core::utf8::to_utf8;
        use std::ffi::{CStr, CString, c_char};
        use std::ptr::null_mut;

        use AllocResult as R;

        let mut out: *mut c_char = null_mut();
        let content = CString::new(
            "café 世界 🌍\n春の海　ひねもすのたり　のたりかな\nشكرا لك.\n
            Cá trèo lên cây cao, khỉ bơi tung tăng mặt hồ!\n
            Thấy em thật là vui khi không buồn và thật buồn khi mà không vui...\n
            Anh nói với họ rằng, có kì lân thực sự và con gà nhà anh đã đấm chết một
            con voi nặng 69 tấn nhưng họ lại bắt anh, anh tự hỏi vì sao nhỉ em?",
        )
        .unwrap();

        let result = to_utf8(content.as_ptr(), &raw mut out);
        let content_str = CStr::from_ptr(out).to_str().unwrap();

        assert_ne!(result, R::C_STRING_CONVERT_ERR);
        assert_ne!(result, R::NULL_DEFERENCE_ERR);
        assert_eq!(result, R::OK);
        assert!(!content_str.is_empty());
        assert_eq!(
            content_str,
            "café 世界 🌍\n春の海　ひねもすのたり　のたりかな\nشكرا لك.\n
            Cá trèo lên cây cao, khỉ bơi tung tăng mặt hồ!\n
            Thấy em thật là vui khi không buồn và thật buồn khi mà không vui...\n
            Anh nói với họ rằng, có kì lân thực sự và con gà nhà anh đã đấm chết một
            con voi nặng 69 tấn nhưng họ lại bắt anh, anh tự hỏi vì sao nhỉ em?"
        );

        let _ = CString::from_raw(out);
    }
}
