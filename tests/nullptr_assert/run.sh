#!/bin/bash

function check_requirements() {
    if ! command -v clang >/dev/null 2>&1; then
        echo "Could not find Clang in your operating system"
        exit 1
    fi
}

function mkdir_build() {
    local build_dir="build"

    if [ ! -d "$build_dir" ]; then
        echo "Could not find: '$build_dir' folder"
        echo "Generating..."

        mkdir -p "$build_dir"
        echo "Successfully  create build dir: $build_dir"
    fi
}

function build_test() {
    local build_dir="build"
    program_name="nullptrassert"

    check_requirements
    mkdir_build

    cd "$build_dir" || exit 1
    cmake -DCMAKE_C_COMPILER=clang \
          -DCMAKE_CXX_COMPILER=clang++ \
          -DZ_DEBUG=1 \
          ..
    
    make
    ./$program_name
}

build_test