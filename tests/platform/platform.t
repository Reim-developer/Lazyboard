#!/usr/bin/perl
use strict;
use warnings;
use lib "../test_lib";
use test_lib qw(gen_cmake gen_base_dir run_test);

# Gen CMakeLists.txt if it doesn't exists.
my $test_name = "platform";
my $base_source = <<END;
// Auto gen base test.
#include <QtGlobal>
#include <cassert>

// clang-format off
enum class Platform : int { 
    LINUX, 
    WINDOWS, 
    MACOS, 
    UNKNOWN 
};

// clang-format on

int hasPlatform() {
    // clang-format off
    #ifdef Q_OS_LINUX
        return static_cast<int>(Platform::LINUX);
    #elif Q_OS_DARWIN
        return static_cast<int>(Platform::MACOS);
    #elif Q_OS_WINDOWS
        return static_cast<int>(Platform::WINDOWS);
    #else
        return static_cast<int>(Platform::UNKNOWN);
    #endif
    // clang-format on
}

int main() {
    int platform = hasPlatform();

    // clang-format off
    #ifdef Q_OS_LINUX
        assert(platform == static_cast<int>(Platform::LINUX));
    #elif Q_OS_DARWIN
        assert(platform == static_cast<int>(Platform::MACOS));
    #elif Q_OS_WINDOWS
        assert(platform static_cast<int>(Platform::WINDOWS));
    #else
        assert(platform static_cast<int>(Platform::UNKNOWN));
    #endif
    // clang-format on
}
END

my $base_cmake = <<'END';
cmake_minimum_required(VERSION 3.19)
project(platform)

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
my $c_type = "cc";
my $build_dir = gen_base_dir("$base_source", "$c_type");
run_test("$build_dir", "$test_name");
print "Test passed."