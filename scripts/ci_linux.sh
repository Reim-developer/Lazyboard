#!/bin/bash
build_dir="build"
release_flags="-DCMAKE_BUILD_TYPE=Release"
qt_static_dir="$build_dir/qt-static"
qt_src_dir="$build_dir/qt-src"
opt_flags="-O3 -march=native -flto -funroll-loops -fomit-frame-pointer -fstrict-aliasing -ftree-vectorize -fvisibility=hidden"
nproc=$(nproc)

create_build_dir() {
    mkdir $build_dir
}

install_base() {
     sudo apt install -y \
        git \
        clang \
        cmake \
        ninja-build \
        build-essential \
        libgl1 \
        python3 \
        patchelf \
        wget \
        perl
}

build_qt_static() {
    mkdir -p "$qt_src_dir"
    cd "$qt_src_dir" || exit

    git clone https://code.qt.io/qt/qt5.git  .
    git checkout v6.5.2
    perl init-repository --module-subset=qtbase

    ./configure -static -release \
        -prefix "$qt_static_dir" \
        -platform linux-clang \
        -opensource -confirm-license \
        -skip qtwebengine \
        -no-qml \
        -no-openssl \
        -no-icu \
        -nomake examples -nomake tests

    make -j"$nproc"
    make install
}

build_zclipboard() {
     cd "$build_dir" || exit

    export PATH="$qt_static_dir/bin:$PATH"

    cmake -G "Ninja" \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_CXX_FLAGS="$opt_flags" \
        $release_flags \
        -DCMAKE_PREFIX_PATH="$qt_static_dir" \
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