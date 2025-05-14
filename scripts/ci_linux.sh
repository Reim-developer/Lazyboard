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
    sudo apt-get install -y git cmake ninja-build desktop-file-utils \
    qt6-base-dev clang wget libfuse3-dev fuse3 libfuse2t64
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

binary_name="zclipboard"
release_dir="zclipboard"
create_release_dir() {
    local assets="assets/icon.png"

    mkdir -p "$release_dir/lib"
    mkdir -p "$release_dir/bin"

    cp "$build_dir/$binary_name" "$release_dir/bin/" 
    cp "$assets" "$release_dir"
}

set_run_script() {
    local script_name="zclipboard"
    cat > "$release_dir/$script_name"  << 'EOF'
#!/bin/bash
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export LD_LIBRARY_PATH="$DIR/lib:$LD_LIBRARY_PATH"
export QT_DEBUG_PLUGINS=1
export QT_PLUGIN_PATH="$DIR"
"$DIR/bin/zclipboard"

register_application() {
    local release_dir="zclipboard"
    local desktop_file="$release_dir/zclipboard.desktop"
    local icon_file="$release_dir/icon.png"

    if [ -f "$desktop_file" ] && [ ! -f "$HOME/.local/share/applications/zclipboard.desktop" ]; then
        mkdir -p ~/.local/share/applications/
        cp "$desktop_file" ~/.local/share/applications/
    fi

    if [ -f "$icon_file" ] && [ ! -f "$HOME/.local/share/icons/icon.png" ]; then
        mkdir -p ~/.local/share/icons/
        cp "$icon_file" ~/.local/share/icons/
    fi

    update-desktop-database ~/.local/share/applications/
}

register_application
EOF

    chmod +x "$release_dir/$script_name"
}

copy_qt_platform_plugin() {
    local qt_plugins="/usr/lib/qt6/plugins"
    local target_dir="$release_dir/platforms"

    mkdir -p "$target_dir"
    cp "$qt_plugins/platforms/libqxcb.so" "$target_dir/"
}

copy_qt_sql_driver() {
    local source_dir="/usr/lib/qt6/plugins/sqldrivers"
    local target_dir="$release_dir/sqldrivers"

    mkdir -p "$target_dir"
    cp "$source_dir"/*.so "$target_dir/"
}

copy_qt_platformtheme_plugin() {
    local qt_plugins="/usr/lib/qt6/plugins"
    local target_dir="$release_dir/platformthemes"

    mkdir -p "$target_dir"
    cp "$qt_plugins/platformthemes/"*.so "$target_dir/"
}

gen_desktop_entry() {
    local desktop_name="zclipboard.desktop"

    cat > "$release_dir/$desktop_name" << EOF
[Desktop Entry]
Name=ZClipboard
Exec=./zclipboard
Icon=icon
Type=Application
Categories=Utility;
EOF
}

setup_so_library() {
    ldd "$build_dir/$binary_name" | \
    awk '/=>/{print $3} /not found/{print $1 " (NOT FOUND)"}' | \
        while read -r lib; do
            if [[ -f "$lib" ]]; then
                cp "$lib" "$release_dir/lib/"
            fi
        done
}

match_options() {
    case "$1" in 
    "install-base") install_base ;;
    "mkdir-build") create_build_dir ;;
    "release-build") build_zclipboard ;;
    "setup-zclipboard")
        create_release_dir
        set_run_script
        setup_so_library
        gen_desktop_entry
        copy_qt_platform_plugin
        copy_qt_platformtheme_plugin
        copy_qt_sql_driver ;;
    *)
    echo "Usage: $0 {install-base |mkdir-build |release-build| setup-zclipboard}"
    exit 1
    esac
}

match_options "$1"