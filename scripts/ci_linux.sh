#!/bin/bash
build_dir="build"
release_flags="-DCMAKE_BUILD_TYPE=Release"
opt_flags="-O3 -march=native -flto -funroll-loops -fomit-frame-pointer -fstrict-aliasing -ftree-vectorize -fvisibility=hidden"
nproc=$(nproc)

create_build_dir() {
    mkdir $build_dir
}

install_base() {
    sudo apt  install -y \
                clang \
                qt6-base-dev \
                qt6-base-private-dev \
                ninja-build \
                cmake \
                build-essential
}

build_zclipboard() {
    cd "$build_dir" || exit
    
    cmake -G "Ninja" \
    -DCMAKE_CXX_COMPILER=clang \
    -DCMAKE_CXX_FLAGS="$opt_flags" \
    $release_flags \
    ..

    ninja -j "$nproc"
}

match_options() {
    case "$1" in 
    "install-base")  install_base ;;

    "mkdir-build")   create_build_dir ;;
    "release-build") build_zclipboard ;;
    *)
        echo "Invalid args $1"
        exit 1
    ;;

    esac
}

match_options "$1"