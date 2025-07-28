#!/bin/bash
build_dir="build"
qt_src_dir="qt-src"
qt_build_dir="qt-build"
qt_install_dir="/opt/qt-static"
qt_version="6.5.3"
release_flags="-DCMAKE_BUILD_TYPE=Release"
opt_flags="-O3 -march=native -flto -funroll-loops -fomit-frame-pointer -fstrict-aliasing -ftree-vectorize -fvisibility=hidden"
nproc=$(nproc)

create_build_dir() {
    mkdir -p "$build_dir"
}

install_base() {
    sudo apt-get update
    sudo apt-get install -y git cmake ninja-build desktop-file-utils \
    clang libnotify-dev libsodium-dev \
    build-essential perl python3 \
    libfontconfig1-dev libfreetype6-dev \
    libx11-dev libx11-xcb-dev libxext-dev libxfixes-dev \
    libxi-dev libxrender-dev libxcb1-dev libxcb-glx0-dev \
    libxcb-keysyms1-dev libxcb-image0-dev libxcb-shm0-dev \
    libxcb-icccm4-dev libxcb-sync-dev libxcb-xfixes0-dev \
    libxcb-shape0-dev libxcb-randr0-dev libxcb-render-util0-dev \
    libxcb-util-dev libxcb-xinerama0-dev libxcb-xkb-dev \
    libxkbcommon-dev libxkbcommon-x11-dev
}

download_qt_source() {
    echo "Downloading Qt source..."
    mkdir -p "$qt_src_dir"
    cd "$qt_src_dir" || exit
    
    if [ -f "qt-everywhere-src-${qt_version}.tar.xz" ]; then
        echo "Qt source already downloaded."
    else
        wget "https://download.qt.io/official_releases/qt/$(echo $qt_version | cut -d. -f1-2)/${qt_version}/single/qt-everywhere-src-${qt_version}.tar.xz"
        tar xf "qt-everywhere-src-${qt_version}.tar.xz"
    fi
    
    cd ..
}

build_static_qt() {
    echo "Building static Qt..."
    mkdir -p "$qt_build_dir"
    cd "$qt_build_dir" || exit
    
    if [ -d "$qt_install_dir/bin" ]; then
        echo "Qt static already built and installed."
        cd ..
        return
    fi
    
     cmake "$qt_src_dir/qt-everywhere-src-$qt_version" \
        -G "Ninja" \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX="$qt_install_dir" \
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_CXX_FLAGS="$opt_flags" \
        -DBUILD_SHARED_LIBS=OFF \
        \
        -DFEATURE_static=ON \
        -DFEATURE_static_runtime=ON \
        -DFEATURE_reduce_exports=ON \
        -DFEATURE_opengl=desktop \
        -DFEATURE_system_png=OFF \
        -DFEATURE_system_jpeg=OFF \
        -DFEATURE_system_zlib=OFF \
        -DFEATURE_fontconfig=ON \
        -DFEATURE_harfbuzz=ON \
        -DFEATURE_xcb=ON \
        -DFEATURE_xkbcommon=ON \
        -DFEATURE_ssl=ON \
        -DFEATURE_widgets=ON \
        -DFEATURE_gui=ON \
        -DFEATURE_network=ON \
        -DFEATURE_concurrent=ON \
        -DFEATURE_xml=ON \
        \
        -DQT_FEATURE_optimize_size=ON \
        -DQT_FEATURE_pkg_config=OFF \
        -DQT_FEATURE_separate_debug_info=OFF \
        -DQT_FEATURE_strip=ON \
        \
        -DQT_BUILD_EXAMPLES=OFF \
        -DQT_BUILD_TESTS=OFF \
        \
        -DQT_SKIP_MODULES=\
            qtwebengine;\
            qt3d;qt5compat;qtactiveqt;qtcharts;\
            qtconnectivity;qtdatavis3d;qtdoc;\
            qtgamepad;qtgraphicaleffects;qthttpserver;\
            qtimageformats;qtlocation;qtlottie;qtmultimedia;\
            qtnetworkauth;qtopcua;qtpositioning;qtpurchasing;qtquick3d;\
            qtquickcontrols2;qtquicktimeline;qtremoteobjects;qtsensors;\
            qtspeech;qtstatemachine;qtsvg;qtvirtualkeyboard;qtwayland;\
            qtwebchannel;qtwebsockets;qtwebview;qtx11extras;qtxmlpatterns
    
    make -j "$nproc"
    sudo make install
    
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