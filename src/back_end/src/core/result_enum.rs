#[repr(C)]
#[allow(non_camel_case_types)]
pub enum AllocResult {
    OK,
    NULL_DEFERENCE_ERR,
    C_STRING_CONVERT_ERR,
}
