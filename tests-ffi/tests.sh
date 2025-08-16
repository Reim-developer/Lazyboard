#!/usr/bin/bash
set -e

function check() {
	local required_tool=$1

	if ! command -v "$required_tool" >/dev/null 2>&1; then 
		echo "$required_tool not found in system"
		exit 
	fi 
}

function build_backend() {
	local backend_dir="src/back_end"
	local tests_ffi_dir="tests-ffi"
	local cargo="cargo"

	check "$cargo"
	cd ..
	if [ ! -d "$backend_dir" ]; then
		echo "$backend_dir not found"
		exit 1
	fi 

	cd "$backend_dir" || exit 1
	$cargo build
	cd ../..
	cd "$tests_ffi_dir" || exit 1
}

function run_ffi_test() {
	local clang_cxx="clang++"
	local static_lib_path="../src/back_end/target/debug/libback_end.a"
	local build_dir="build"
	local sqlite_lib="sqlite3"
	check "$clang_cxx"

	echo -e "\e[0;32m[+] Build backend:\e[0;37m"
	build_backend
	echo -e "\e[0;32m[+] Build done\e[0;37m"

	if [ ! -d "$build_dir" ]; then 
		mkdir -p "$build_dir"
	fi

	for file in *.cxx; do
		build_output=$(basename "$file" ".cxx")
		file_name=$(basename "$file")

		$clang_cxx "$file" -l"$sqlite_lib" "$static_lib_path" -o "$build_dir/$build_output"
		echo
		echo -e -n "\e[0;32m[+] Test for $file_name:\e[0;37m"

		time_test=$( {
			time ./"$build_dir/$build_output"
		} )

		status_code=$?
		echo -e -n "$time_test"
		echo -e "\e[0;32m[+] Test for $file_name success with status code: $status_code\e[0;37m"

		for _ in {1..25}; do
			printf "_"
		done
		echo 
	done
}

function main() {
	run_ffi_test
}

main