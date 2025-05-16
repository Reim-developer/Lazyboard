#!/bin/bash

trans() {
    local trans_file="language.hpp"
    local trans_script="translate.py"
    local gen_path="../src/language/include"

    cd ".." || exit
    cd "tools" || exit

    python "$trans_script"
    cp "$trans_file" "$gen_path"
    rm -rf "$trans_file"
}

trans