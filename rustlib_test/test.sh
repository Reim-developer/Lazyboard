#!/bin/bash

function test_lib() {
    if [ ! -d "build" ]; then 
        mkdir -p "build"
    fi

    cargo build

    local rust_lib="target/debug/librustlib_test.a"
    clang++ "main.cxx" "$rust_lib" -o "build/main"

    "./build/main"
}

test_lib