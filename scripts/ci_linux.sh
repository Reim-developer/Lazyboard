#!/bin/bash
build_dir="build"
qt_build_dir="qt-build"

mkdir -p "$qt_build_dir"

release_flags="-DCMAKE_BUILD_TYPE=Release"
qt_src_dir="$qt_build_dir/qt-src"
qt_static_dir="$(cd "$qt_build_dir" && pwd)/qt-src/qtbase/build/qt-static"

opt_flags="-O3 -march=native -flto -funroll-loops -fomit-frame-pointer -fstrict-aliasing -ftree-vectorize -fvisibility=hidden"
nproc=$(nproc)

create_build_dir() {
    mkdir -p "$build_dir" "$qt_build_dir"
}

install_base() {
    sudo apt-get update
    sudo apt-get install -y git python3 perl build-essential clang cmake ninja-build \
    libgl1-mesa-dev libx11-dev libxext-dev libxrender-dev \
    libxcb1-dev libx11-xcb-dev libglu1-mesa-dev \
    libfontconfig1-dev libmysqlclient-dev \
    libfreetype6-dev libx11-dev libx11-xcb-dev \
    libxext-dev libxfixes-dev libxi-dev \
    libxrender-dev libxcb1-dev \
    libxcb-glx0-dev libxcb-keysyms1-dev \
    libxcb-image0-dev libxcb-shm0-dev libxcb-icccm4-dev \
    libxcb-sync-dev libxcb-xfixes0-dev libxcb-shape0-dev \
    libxcb-randr0-dev libxcb-render-util0-dev libxcb-util-dev \
    libxcb-xinerama0-dev libxcb-xkb-dev libxkbcommon-dev \
    libxkbcommon-x11-dev libatspi2.0-dev dbus-x11 libpcre2-dev
}

build_qt_static() {
    mkdir -p "$qt_src_dir"
    cd "$qt_src_dir" || exit

    git clone https://github.com/qt/qt5.git  .
    git checkout v6.5.2
    perl init-repository -f --module-subset=qtbase

    cd qtbase || exit
    mkdir -p build && cd build || exit

    ../configure -static -release \
        -prefix "$qt_static_dir" \
        -platform linux-clang \
        -opensource -confirm-license \
        -nomake examples -nomake tests \
        -developer-build \
        -- -Wno-dev CXXFLAGS+="-DFORCE_STATIC_QT"

    cmake --build . --parallel "$nproc"
    cmake --install . --prefix "$qt_static_dir"

    cd ../.. || exit
}

build_zclipboard() {
    cd "$build_dir" || exit

    cmake -G "Ninja" \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_CXX_FLAGS="$opt_flags -DFORCE_STATIC_QT" \
        "$release_flags" \
        -DCMAKE_PREFIX_PATH="$qt_static_dir" \
        -DQt6_ROOT="$qt_static_dir" \
        -DQt6_DIR="$qt_static_dir/lib/cmake/Qt6" \
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