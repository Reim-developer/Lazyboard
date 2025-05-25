#!/usr/bin/perl
use strict;
use warnings;
use lib "../test_lib";
use test_lib qw(gen_cmake gen_base_dir run_test tool_check);

# Test name.
my $test_name = "translator";

# Auto generate base translator test if 'main.cc' is not exists.
my $cpp_source = <<END;
// Auto generate Test base.
#include "../../../src/language/include/language.hpp"
#include <iostream>
using namespace zclipboard::language;

int main() {
    std::cout << DISCONNECT_VI << std::endl;
    std::cout << DISCONNECT_EN << std::endl;
    return 0;
}
END

my $cmake_base = <<'END';
cmake_minimum_required(VERSION 3.19)
project(translator)

set(CMAKE_CXX_STANDARD 17)
set(CXX_SOURCE)
set(CXX_HEADER)

file(GLOB_RECURSE SOURCES "src/*.cc")
file(GLOB_RECURSE HEADER_SOURCES "src/*.hpp")

foreach(SOURCE_FILE ${SOURCES})
    list(APPEND CXX_SOURCE ${SOURCE_FILE})
endforeach()

foreach(HEADER_FILE ${HEADER_SOURCES})
    list(APPEND CXX_HEADER ${HEADER_FILE})
endforeach()

add_executable(${PROJECT_NAME} ${CXX_SOURCE} ${CXX_HEADER} ${ASSETS})
END

die "[ERR] Could not find CMake" unless tool_check("cmake");
die "[ERR] Could not find Clang" unless tool_check("clang");
die "[ERR] Could not find Make" unless tool_check("make");

# If CMakeLists.txt is not exists & base directory test is not exists.
gen_cmake("$test_name", "$cmake_base");
my $c_type = "cc"; # C++
my $build_dir = gen_base_dir("$cpp_source", "$c_type");
run_test("$build_dir", "$test_name");

print("Test passed.\n")