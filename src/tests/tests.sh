#!/usr/bin/bash

function main() {
	local clang_cxx="clang++"
	local build_dir="build"
	local static_lib="../back_end/target/debug/libback_end.a"
	local config_test="config.cxx"

	cd ..
	cd "back_end" || exit 1
	cargo build
	cd .. 
	cd "tests" || exit 1
	
	if [ ! -d "$build_dir" ]; then
		mkdir -p "$build_dir"
	fi 

	$clang_cxx "$config_test" "$static_lib" -o "$build_dir/config_test"
	./"$build_dir/config_test"
}

main