#![deny(clippy::all, clippy::pedantic, clippy::nursery, clippy::perf)]

use std::{ffi::CString, os::raw::c_char};
use std::ptr::null_mut;

#[unsafe(no_mangle)]
pub unsafe extern "C" fn greet() {
    println!("Hello World");
}

#[unsafe(no_mangle)]
pub extern "C" fn get_reim_name() -> *mut c_char {
    CString
        ::new("REIM DEVELOPER")
        .map(|name| name.into_raw())
        .unwrap_or(null_mut())
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn free_name(c_string: *mut c_char) {
    if !c_string.is_null() {
        unsafe  {
            let _ = CString::from_raw(c_string);
        }
    }
}