#!/usr/bin/perl
use strict;
use warnings;
use lib "../test_lib";
use test_lib qw(gen_cmake gen_base_dir run_test);

# Gen CMakeLists.txt if it doesn't exists.
my $test_name = "setting_qt";
my $base_source = <<END;
#include <iostream>

int main() {
    std::cout << "hELLO WORLD" << std::endl;
    return 0;
}
END

my $base_cmake = <<'END';
cmake_minimum_required(VERSION 3.19)
project(setting_qt)

set(CMAKE_CXX_STANDARD 17)
set(CXX_SOURCE)
set(CXX_HEADER)

find_package(Qt6 REQUIRED Core)

file(GLOB_RECURSE SOURCES "src/*.cc")
file(GLOB_RECURSE HEADER_SOURCES "src/*.hpp")

foreach(SOURCE_FILE ${SOURCES})
    list(APPEND CXX_SOURCE ${SOURCE_FILE})
endforeach()

foreach(HEADER_FILE ${HEADER_SOURCES})
    list(APPEND CXX_HEADER ${HEADER_FILE})
endforeach()

add_executable(${PROJECT_NAME} ${CXX_SOURCE} ${CXX_HEADER} ${ASSETS})

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE Qt6::Core
)
END

gen_cmake("$test_name", "$base_cmake");
my $build_dir = gen_base_dir("$base_source");
run_test("$build_dir", "$test_name");
print "Test passed."