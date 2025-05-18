#!/bin/bash

sync_aur() {
    local tool_dir="tools"
    local tool_file="sync_aur.py"

    cd "../.." || exit

    cd "$tool_dir" || exit

    if ! command -v python > /dev/null; then
        echo "Could not find Python in this system. Exit now"
        exit 1
    fi

    python "$tool_file" "../PKGBUILD" "../zclipboard/PKGBUILD" --verbose
}

sync_aur