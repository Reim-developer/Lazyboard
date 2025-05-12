#!/bin/bash
os_type=$(uname -s)
program_name="zclipboard"
build_dir="../build"
debug_flag="-DCMAKE_BUILD_TYPE=Debug"
wall_flag="-Wall"

clang_detect() {
    if command -v clang >/dev/null 2>&1; then
        echo "[OK] Clang is already install in your os..."
    else
        echo "[BAD] Clang not found in your os. Please install them before build."
        exit 1
    fi
}

cmake_detect() {
    if command -v cmake >/dev/null 2>&1; then
        echo "[OK] Cmake is already install in your os..."
    else
        echo "[BAD] CMake not found in your os. Please install them before build."
        exit 1
    fi
}

debug_build() {
    clang_detect
    cmake_detect
    
    cd "$build_dir" || exit 1
    cmake -G "Ninja" \
        "$debug_flag" ..

    ninja
    ./"$program_name"
}

normal_build() {
     clang_detect
     cmake_detect

    cd "$build_dir" || exit 1
    cmake "$wall_flag" \
        -DCMAKE_CXX_COMPILER=clang \
        ..
        
    make
    ./"$program_name"
}

invalid_args() {
    echo "Invalid argument build: $1"
    exit 1
}

match_build() {
    case "$1" in "debug") debug_build ;;
    "") normal_build ;;
    *) invalid_args "$1" ;;
    esac
}

os_detect() {
    case $os_type in "Linux" | "Darwin")
        match_build "$1"
    ;;
        
    esac
}

os_detect "$1"