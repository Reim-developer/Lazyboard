#!/bin/bash
os_type=$(uname -s)
build_dir="../build"
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

bear_detect() {
    if command -v bear >/dev/null 2>&1; then
        echo "[OK] Bear is already install in your os..."

    else
        echo "[BAD] Bear not found in your os. Please install them before build."
        exit 1
    fi 
}

gen_compile_commands() {
    clang_detect
    cmake_detect
    bear_detect

    cd "$build_dir" || exit 1

    cmake "$wall_flag" \
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_C_COMPILER_LAUNCHER=ccache \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_CXX_COMPILER_LAUNCHER=ccache \
        -DZ_DEBUG=1 \
        ..
        
    bear -- make
}

invalid_args() {
    echo "Invalid argument build: $1"
    exit 1
}

match_build() {
    if [ ! -d $build_dir ]; then
        mkdir "$build_dir"
    fi
    
    gen_compile_commands
}

os_detect() {
    case $os_type in "Linux" | "Darwin")
        match_build "$1"
    ;;
        
    esac
}

os_detect "$1"