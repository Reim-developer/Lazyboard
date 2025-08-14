#!/bin/bash
set -e

current_dir=$(basename "$(pwd)")

function check() {
	local require_tool=$1

	if ! command -v "$require_tool" >/dev/null 2>&1; then 
		echo "Could not find $require_tool in system"
		exit
	fi 
}

function fmt() {
	local clang_fmt="clang-format"
	check "$clang_fmt"
	local tools_dir="tools"
	local clang_fmt_cfg=".clang-format"

	if [[ "$tools_dir" == "$current_dir" ]]; then 
		cd .. || exit 1
	fi 

	if [ ! -f "$clang_fmt_cfg" ]; then
		echo "$clang_fmt_cfg not found"
		exit 1
	fi 

	find . -name "*.cxx" -o -name "*.hxx" | while IFS= read -r file; do
		file_base_name=$(basename "$file")

		echo -e "\e[0;32m[+] Format file: $file_base_name\e[0;37m"
		"$clang_fmt" -i "$file"
	done 
}

function main() {
	fmt 
}

main