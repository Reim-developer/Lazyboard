#!/bin/bash

change_work_dir() {
    local test_folder="tests"
    local trans_file="encrypt_t.py"
    local test_name="Encrypt Test"

    cd ../.. || exit
    cd "$test_folder" || exit

    if ! command -v python3 >/dev/null; then
        echo "Could not find Python in this system."
        echo "Test FAILED."
        exit 1
    fi

    echo "Current Test Directory: $(pwd)"
    echo "Test Name: $test_name"
    python "$trans_file"
}

change_work_dir