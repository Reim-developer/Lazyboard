#!/bin/bash
set -e
program_name="Lazyboard"
compile_command="compile_commands.json"
build_dir="../build"
gdb_prog="gdb"
wall_flag="-Wall"

function check() {
    if ! command -v "$1" >/dev/null 2>&1; then 
        echo "[ERR] Could not find $1 in your system. Aborting"
        exit 1
    fi
}

function back_end_test() {
    check "cargo"
    check "rustup"

    local back_end="src/back_end"
    cd ..
    cd "$back_end" || exit 1

    cargo test
}

function debug_build() {
    check "clang"
    check "cmake"

    check "cargo"
    check "rustup"

    cd ..
    cd "src/back_end" || exit 1
    cargo build

    cd ..
    local show_gui="$1"

    if [ ! -d $build_dir ]; then
        mkdir "$build_dir"
    fi

    cd "$build_dir" || exit 1

    cmake "$wall_flag" \
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_C_COMPILER_LAUNCHER=ccache \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_CXX_COMPILER_LAUNCHER=ccache \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
        ..
        
    make

    if [[ $show_gui == 1 ]]; then
        ./"$program_name"
    fi

    cp "$compile_command" ..
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

function debug_gdb() {
    checl "gdb"
    local gdb_cmd="../commands.gdb"
    local not_show_gui=0

    debug_build $not_show_gui
    "$gdb_prog" --batch -x "$gdb_cmd" "$program_name"
}

function pre_push() {
    linter_check

    local branch="$1"

    git push origin "$branch"
}

function main() {
    case $1 in 
        "debug-build") {
            local show_gui=1
            debug_build $show_gui
        }   ;;
        "debug-build-noshow") {
            local show_gui=0
            debug_build $show_gui
        } ;;
        "debug-gdb") debug_gdb ;;
        "check-backend")  {
            local option="clippy"
            linter_check $option
        };;
        "check-frontend") {
            local option="clang-tidy"
            linter_check "$option"
        } ;;
        "backend-test") back_end_test ;;
        "push-dev") {
            local dev_branch="dev"
            pre_push $dev_branch
        } ;;
        "push-master") {
            local master_branch="master"
            pre_push $master_branch
        } ;;
        "push-stable") {
            local stable_branch="stable"
            pre_push $stable_branch
        } ;;
        *) {    
            echo "Invalid option: $1"
            exit 1
        } ;;
    esac  
}

main "$1"
