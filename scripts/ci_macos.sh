#!/bin/bash
build_entry="build"
opt_flags="-O3 -march=native -flto -funroll-loops -fomit-frame-pointer -fstrict-aliasing -ftree-vectorize -fvisibility=hidden"
app_name="zclipboard"
bundle_name="$app_name.app"

install_homebrew() {
    if ! command -v brew > /dev/null; then 
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi
}

setup_env() {
    eval "$(/opt/homebrew/bin/brew shellenv)"
}

install_dependencies() {
    brew install --formula cmake qt@6

    export PATH="/opt/homebrew/opt/qt@6/bin:$PATH"
    export QT_DIR="/opt/homebrew/opt/qt@6"
}

create_build_dir() {
    mkdir -p "$build_entry"
    cd "$build_entry" || exit
}

cfg_and_build() {
    cd "$build_entry" || exit

    cmake \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_CXX_FLAGS="$opt_flags" \
        -G "Ninja" \
        ..

    ninja
}

setup_icon() {
    mkdir -p build/icon.iconset

    sips -z 16 16     assets/icon.png --out build/icon.iconset/icon_16x16.png
    sips -z 32 32     assets/icon.png --out build/icon.iconset/icon_16x16@2x.png
    sips -z 32 32     assets/icon.png --out build/icon.iconset/icon_32x32.png
    sips -z 64 64     assets/icon.png --out build/icon.iconset/icon_32x32@2x.png
    sips -z 128 128   assets/icon.png --out build/icon.iconset/icon_128x128.png
    sips -z 256 256   assets/icon.png --out build/icon.iconset/icon_128x128@2x.png
    sips -z 256 256   assets/icon.png --out build/icon.iconset/icon_256x256.png
    sips -z 512 512   assets/icon.png --out build/icon.iconset/icon_256x256@2x.png
    sips -z 1024 1024 assets/icon.png --out build/icon.iconset/icon_512x512@2x.png

    iconutil -c icns build/icon.iconset -o build/icon.icns

    rm -rf build/icon.iconset
}

create_app_bundle() {
    local binary_path="$build_entry/$app_name"
    local bundle_path="$bundle_name/Contents"

    mkdir -p "$bundle_path/MacOS"
    mkdir -p "$bundle_path/Resources"

    cp "$binary_path" "$bundle_path/MacOS/"

    cat > "$bundle_path/Info.plist" <<EOL
        <?xml version="1.0" encoding="UTF-8"?>
        <!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
        <plist version="1.0">
        <dict>
            <key>CFBundleExecutable</key>
            <string>$app_name</string>
            <key>CFBundleIconFile</key>
            <string>icon.icns</string>
            <key>CFBundleIdentifier</key>
            <string>com.yourcompany.$app_name</string>
            <key>CFBundleName</key>
            <string>ZClipboard</string>
            <key>CFBundlePackageType</key>
            <string>APPL</string>
            <key>LSMinimumSystemVersion</key>
            <string>10.13.0</string>
        </dict>
        </plist>
EOL

    if [ -f "$build_entry/icon.icns" ]; then 
        cp "$build_entry/icon.icns" "$bundle_path/Resources/"
    fi
}

setup_release() {
    if [ -d "$bundle_name" ]; then
        tar -czf "$app_name-macOS.tar.gz" "$bundle_name"
    fi
}

match_options() {
    case $1 in 
    "install-base") install_homebrew ;;
    "install-libs") install_dependencies ;;
    "setup-build") create_build_dir ;;
    "build-release") cfg_and_build ;;
    "setup-icon") setup_icon ;;
    "create-bundle") create_app_bundle ;;
    "setup-release") setup_release ;;

    *) echo "Missing arg: $1" && exit 1 ;;
    esac
}

match_options "$1"