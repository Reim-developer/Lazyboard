#!/bin/bash

function check_gdb() {
	if ! command -v gdb >/dev/null 2>&1; then
		echo "Could not find GDB in system. Aborting"
		exit 1
	fi 
}

function main() {
	local build_dir="build"
	local program_name="zClipboard"

	check_gdb
	cd ..

	if [ ! -d "$build_dir" ]; then 
		mkdir -p "$build_dir"
	fi 

	cd "$build_dir" || exit 1
	gdb "$program_name" <<EOF
	
	run
EOF
}

main