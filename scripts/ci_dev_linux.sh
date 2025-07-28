#!/bin/bash
build_dir="build"

qt_build_dir="qt-build"
qt_install_dir="/opt/qt-static"
qt_version="6.9.1"
release_flags="-DCMAKE_BUILD_TYPE=Release"
opt_flags="-O1 -funroll-loops -fomit-frame-pointer -fstrict-aliasing -ftree-vectorize -fvisibility=hidden"
nproc=$(nproc)

create_build_dir() {
    mkdir -p "$build_dir"
}

install_base() {
    sudo apt-get update
    sudo apt-get install -y cmake ninja-build desktop-file-utils \
        clang  libclang-dev \
        build-essential perl python3 python3-pip \
        libfontconfig1-dev libfreetype6-dev \
        libx11-dev libx11-xcb-dev libxext-dev libxfixes-dev \
        libxi-dev libxrender-dev libxcb1-dev libxcb-glx0-dev \
        libxcb-keysyms1-dev libxcb-image0-dev libxcb-shm0-dev \
        libxcb-icccm4-dev libxcb-sync-dev libxcb-xfixes0-dev \
        libxcb-shape0-dev libxcb-randr0-dev libxcb-render-util0-dev \
        libxcb-util-dev libxcb-xinerama0-dev libxcb-xkb-dev \
        libxkbcommon-dev libxkbcommon-x11-dev \
        libgl1-mesa-dev libegl1-mesa-dev libgles2-mesa-dev \
        libdrm-dev libxkbfile-dev libxtst-dev libxshmfence-dev \
        libxrandr-dev libxcursor-dev libxcomposite-dev libudev-dev \
        libdbus-1-dev gperf libnss3-dev libharfbuzz-dev \
        libprotobuf-dev protobuf-compiler libssl-dev libxcb-cursor-dev

    sudo pip3 install html5lib spdx-tools
}

download_qt_source() {
    local qt_src_dir="qt-src"

    echo "Downloading Qt source..."
    mkdir -p "$qt_src_dir"
    cd "$qt_src_dir" || exit
    
    wget "https://download.qt.io/official_releases/qt/$(echo $qt_version | cut -d. -f1-2)/${qt_version}/single/qt-everywhere-src-${qt_version}.tar.xz"
    tar xf "qt-everywhere-src-${qt_version}.tar.xz"
    
    cd ..
}

build_static_qt() {
    echo "Building static Qt..."
    mkdir -p "$qt_build_dir"

    cd "$qt_build_dir" || exit 1

    echo "Downloading Qt prebuilt libclang..."
    wget -O libclang.7z "https://download.qt.io/development_releases/prebuilt/libclang/qt/libclang-release_18.1.7-based-linux-Ubuntu22.04-gcc11.2-x86_64.7z"
    mkdir -p libclang
    7z x libclang.7z -olibclang

    local skip_modules="qtwebengine;qt3d;qt5compat;qtactiveqt;qtcharts;qtconnectivity;qtdatavis3d;qtdoc;qtgamepad;qtgraphicaleffects;qthttpserver;qtimageformats;qtlocation;qtlottie;qtmultimedia;qtnetworkauth;qtopcua;qtpositioning;qtpurchasing;qtquick3d;qtquickcontrols2;qtquicktimeline;qtremoteobjects;qtsensors;qtspeech;qtstatemachine;qtsvg;qtvirtualkeyboard;qtwayland;qtwebchannel;qtwebsockets;qtwebview;qtx11extras;qtxmlpatterns"
    cmake "../qt-src/qt-everywhere-src-$qt_version" \
        -G "Ninja" \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX="$qt_install_dir" \
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_CXX_FLAGS="$opt_flags" \
        -DBUILD_SHARED_LIBS=OFF \
        -DQT_FEATURE_static=ON \
        -DQT_FEATURE_static_runtime=ON \
        -DQT_FEATURE_reduce_exports=ON \
        -DQT_FEATURE_opengl=ON\
        -DQT_FEATURE_system_png=OFF \
        -DQT_FEATURE_system_jpeg=OFF \
        -DQT_FEATURE_system_zlib=OFF \
        -DQT_FEATURE_fontconfig=ON \
        -DQT_FEATURE_harfbuzz=ON \
        -DQT_FEATURE_xcb=ON \
        -DQT_FEATURE_xkbcommon=ON \
        -DQT_FEATURE_ssl=OFF \
        -DQT_FEATURE_widgets=ON \
        -DQT_FEATURE_gui=ON \
        -DQT_FEATURE_network=ON \
        -DQT_FEATURE_concurrent=ON \
        -DQT_FEATURE_xml=ON \
        -DQT_FEATURE_optimize_size=ON \
        -DQT_FEATURE_pkg_config=OFF \
        -DFEATURE_sql_=ON \
        -DQT_FEATURE_separate_debug_info=OFF \
        -DQT_FEATURE_strip=ON \
        -DQT_BUILD_EXAMPLES=OFF \
        -DQT_BUILD_TESTS=OFF \
        -DQT_FEATURE_clang=ON \
        -DQT_FEATURE_clangcpp=ON \
        -DCMAKE_PREFIX_PATH="$PWD/libclang" \
        -DQT_SKIP_MODULES="$skip_modules"
    
    ninja -j "$nproc"
    sudo ninja install
    
    cd ..
}

build_zclipboard() {
    cd "$build_dir" || exit
    export PATH="$qt_install_dir/bin:$PATH"
    
    cmake -G "Ninja" \
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_CXX_FLAGS="$opt_flags" \
        -DCMAKE_PREFIX_PATH="$qt_install_dir" \
        -DQT_QMAKE_EXECUTABLE="$qt_install_dir/bin/qmake" \
        -DBUILD_SHARED_LIBS=OFF \
        "$release_flags" \
        ..

    ninja -j "$nproc"
    
    strip -s zClipboard
}

verify_portable() {
    echo "Verifying portable binary..."
    cd "$build_dir" || exit
    
    echo "Dynamic dependencies:"
    ldd zClipboard || echo "No dynamic dependencies (fully static)"
    
    echo "Binary size:"
    ls -lh zClipboard
    
    echo "Symbol table:"
    nm -D zClipboard 2>/dev/null || echo "No dynamic symbols (fully stripped)"
}

match_options() {
    case "$1" in 
    "install-base") install_base ;;
    "mkdir-build") create_build_dir ;;
    "download-qt") download_qt_source ;;
    "build-static-qt") build_static_qt ;;
    # "release-build") build_zclipboard ;;
    # "verify-portable") verify_portable ;;
    *)
    echo "Usage: $0 {install-base |mkdir-build |download-qt |build-static-qt |release-build |verify-portable}"
    exit 1
    esac
}

match_options "$1"