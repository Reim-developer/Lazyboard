#!/bin/bash
change_work_dir() {
    local test_folder="tests/platform"
    local trans_file="platform.t"
    local test_name="Platfrom Test"

    cd ../.. || exit
    cd "$test_folder" || exit

    if ! command -v perl >/dev/null; then
        echo "Could not find Perl in this system."
        echo "Test FAILED."
        exit 1
    fi

    echo "Current Test Directory: $(pwd)"
    echo "Test Name: $test_name"
    perl "$trans_file"
}

change_work_dir