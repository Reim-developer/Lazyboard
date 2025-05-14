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
    sudo apt-get install -y git cmake ninja-build \
    qt6-base-dev clang wget libfuse3-dev fuse3
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

build_appimage() {
    wget -O linuxdeployqt https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage 
    chmod +x linuxdeployqt

    APPNAME=zclipboard
    APPDIR="${APPNAME}.AppDir"


    mkdir -p "$APPDIR"

    cp build/$APPNAME "$APPDIR/"
    cp assets/icon.png "$APPDIR/"

    cat > "$APPDIR/$APPNAME.desktop" << EOL
          [Desktop Entry]
          Name=zClipboard
          Exec=$APPNAME
          Icon=icon
          Type=Application
          Categories=Utility;Qt;
          Comment=A clipboard manager with networking support
EOL

    ./linuxdeployqt zclipboard.AppDir/zclipboard -appimage
}

match_options() {
    case "$1" in 
    "install-base") install_base ;;
    "mkdir-build") create_build_dir ;;
    "build-qt") build_qt_static ;;
    "release-build") build_zclipboard ;;
    "image-build") build_appimage ;;
    *)
    echo "Usage: $0 {install-base |mkdir-build |release-build| image-build}"
    exit 1
    esac
}

match_options "$1"