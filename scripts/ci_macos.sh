#!/bin/bash
build_entry="build"
opt_flags="-O3 -march=native -flto -funroll-loops -fomit-frame-pointer -fstrict-aliasing -ftree-vectorize -fvisibility=hidden"

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
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_CXX_FLAGS="$opt_flags" \
        -G "Ninja" \
        ..

    ninja
}

match_options() {
    case $1 in 
    "install-base") install_homebrew ;;
    "install-libs") install_dependencies ;;
    "setup-build") create_build_dir ;;
    "build-release") cfg_and_build ;;

    *) echo "Missing arg: $1" && exit 1 ;;
    esac
}

match_options "$1"