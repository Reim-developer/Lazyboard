#!/bin/bash

function test_lib() {
    if [ ! -d "build" ]; then 
        mkdir -p "build"
    fi

    cargo build

    local rust_lib="target/debug/libffi_rs.a"
    clang++ "test_lib.cxx" "$rust_lib" -o "build/test_lib"

    "./build/test_lib"
}

test_lib