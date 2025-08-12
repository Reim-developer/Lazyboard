#!/bin/bash
set -e
build_dir="build"
release_flags="-DCMAKE_BUILD_TYPE=Release"
opt_flags="-O3 -march=native -flto -funroll-loops -fomit-frame-pointer -fstrict-aliasing -ftree-vectorize -fvisibility=hidden"
nproc=$(nproc)

install_dependency() {
    sudo apt-get update
    sudo apt-get install -y git cmake \
    qt6-base-dev clang 
}

function check() {
    if ! command -v "$1" >/dev/null 2>&1; then 
        echo "[ERR] Could not find $1 in your system. Aborting"
        exit 1
    fi
}

function linter_check() {
    local options=$1

    if [[ $options == "clippy" ]]; then 
        local cargo="cargo"
        local backend="src/back_end"
        check "$cargo"

        cd ..
        cd "$backend" || exit 1
        "$cargo" clippy \
        --all-targets --all-features \
        -- -D clippy::all -D clippy::pedantic \
        -D clippy::nursery -D clippy::perf

    else 
        local clang_tidy="clang-tidy"
        check "$clang_tidy"

        cd ..
        clang-tidy src/**/*.cxx -p=build
    fi
}


build_backend() {
	local cargo="cargo"
	local back_end="src/back_end"
	check "$cargo"
	check "rustup"

	cd ..
	cd "$back_end" || exit 1
	"$cargo" build --release
}

backend_test() {
    local cargo="cargo"
	local back_end="src/back_end"
	check "$cargo"
	check "rustup"

    cd ..
    cd "$back_end" || exit 1
    "$cargo" test
}

build_frontend() {
	cd ..

	if [ ! -d "$build_dir" ]; then 
    	mkdir -p "$build_dir"
	fi

    cd "$build_dir" || exit

    cmake -DCMAKE_C_COMPILER=clang \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_CXX_FLAGS="$opt_flags" \
        "$release_flags" \
        ..

    make -j "$nproc"
}

match_options() {
    case "$1" in 
    "install_dependency") install_dependency ;;
    "frontend-build") build_frontend ;;
	"backend-build") build_backend ;;
    "frontend-check") {
        local clang_tidy="clang-tidy"
        linter_check "$clang_tidy"
    } ;;
    "backend-check") {
        local clippy="clippy"
        linter_check "$clippy"
    } ;;
    "backend-test") {
        backend_test
    } ;;
    *)
    echo "Usage: $0 {install_dependency | frontend-build | backend-build}"
    exit 1
    esac
}

match_options "$1"