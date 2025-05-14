#!/bin/bash
build_dir="build"
release_flags="-DCMAKE_BUILD_TYPE=Release"
opt_flags="-O3 -march=native -flto -funroll-loops -fomit-frame-pointer -fstrict-aliasing -ftree-vectorize -fvisibility=hidden"
nproc=$(nproc)

create_build_dir() {
    mkdir -p "$build_dir"
}

install_base() {
    sudo apt-get update
    sudo apt-get install -y git cmake ninja-build qt6-base-dev clang
}

build_zclipboard() {
    cd "$build_dir" || exit

    cmake -G "Ninja" \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_CXX_FLAGS="$opt_flags" \
        "$release_flags" \
        ..

    ninja -j "$nproc"
}

match_options() {
    case "$1" in 
    "install-base") install_base ;;
    "mkdir-build") create_build_dir ;;
    "build-qt") build_qt_static ;;
    "release-build") build_zclipboard ;;
    *)
    echo "Usage: $0 {install-base |mkdir-build |build-qt |release-build}"
    exit 1
    esac
}

match_options "$1"