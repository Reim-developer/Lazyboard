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
    sudo apt-get update
    sudo apt-get install -y ccache git python3 perl build-essential clang cmake ninja-build \
    libgl1-mesa-dev libx11-dev libxext-dev libxrender-dev \
    libxcb1-dev libx11-xcb-dev libglu1-mesa-dev \
    libxcb-render0-dev \
    libxcb-shape0-dev \
    libxcb-xfixes0-dev \
    libxcb-shm0-dev \
    libxcb-atom1-dev \
    libxcb-aux0-dev \
    libxcb-composite0-dev \
    libxcb-cursor-dev \
    libxcb-damage0-dev \
    libxcb-dpms0-dev \
    libxcb-dri2-0-dev \
    libxcb-dri3-dev \
    libxcb-event-dev \
    libxcb-ewmh-dev \
    libxcb-glx0-dev \
    libxcb-icccm4-dev \
    libxcb-image0-dev \
    libxcb-keysyms1-dev \
    libxcb-present-dev \
    libxcb-randr0-dev \
    libxcb-record0-dev \
    libxcb-render-util0-dev \
    libxcb-res0-dev \
    libxcb-screensaver0-dev \
    libxcb-sync-dev \
    libxcb-util-dev \
    libxcb-xevie0-dev \
    libxcb-xf86dri0-dev \
    libxcb-xinerama0-dev \
    libxcb-xinput-dev \
    libxcb-xkb-dev \
    libxcb-xprint0-dev \
    libxcb-xtest0-dev \
    libxcb-xv0-dev \
    libxcb-xvmc0-dev \
    libxkbcommon-dev \
    libxkbcommon-x11-dev
}

build_qt_static() {
    mkdir -p "$qt_src_dir"
    cd "$qt_src_dir" || exit

    git clone https://github.com/qt/qt5.git .
    git checkout v6.5.2
    perl init-repository -f --module-subset=qtbase

    export CC="ccache clang"
    export CXX="ccache clang++"

    cd qtbase  || exit

    ./configure -static -release \
        -prefix "$qt_static_dir" \
        -platform linux-clang \
        -opensource -confirm-license \
        -nomake examples -nomake tests \
        -developer-build \
        -- -Wno-dev CXXFLAGS+="-DFORCE_STATIC_QT"

    cmake --build . --parallel "$nproc"
    cmake --install . --prefix "$qt_static_dir"

    cd .. && cd .. | exit
}

build_zclipboard() {
     cd "$build_dir" || exit

    export PATH="$qt_static_dir/bin:$PATH"

    cmake -G "Ninja" \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_CXX_FLAGS="$opt_flags -DFORCE_STATIC_QT" \
        "$release_flags" \
        -DCMAKE_PREFIX_PATH="$qt_static_dir" \
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