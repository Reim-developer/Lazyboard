#!/usr/bin/perl
use strict;
use warnings;
use File::Path qw(make_path);

sub gen_cpp_test {
    my ($cpp_file_path) = @_;

    my $cpp_source = <<END;
/*
* Auto generate Test base.
*/
#include "../../../src/language/include/language.hpp"
#include <iostream>
using namespace zclipboard::language;

int main() {
    std::cout << DISCONNECT_VI << std::endl;
    std::cout << DISCONNECT_EN << std::endl;
    return 0;
}
END
    print $cpp_file_path "$cpp_source";
}

sub write_cmake {
    my ($cmakeFile, $test_name) = @_;

    my $cmake_source = <<"END";
cmake_minimum_required(VERSION 3.19)
project($test_name)

set(CMAKE_CXX_STANDARD 17)
set(CXX_SOURCE)
set(CXX_HEADER)

file(GLOB_RECURSE SOURCES "src/*.cc")
file(GLOB_RECURSE HEADER_SOURCES "src/*.hpp")

foreach(SOURCE_FILE \${SOURCES})
    list(APPEND CXX_SOURCE \${SOURCE_FILE})
endforeach()

foreach(HEADER_FILE \${HEADER_SOURCES})
    list(APPEND CXX_HEADER \${HEADER_FILE})
endforeach()

add_executable(\${PROJECT_NAME} \${CXX_SOURCE} \${CXX_HEADER} \${ASSETS})
END

    print $cmakeFile "$cmake_source";
}

sub gen_cmake {
    my $test_name="translator";
    my $fileName = "CMakeLists.txt";

    if(! -e $fileName) {
        print("[WARN] Could not find $fileName. Generate new now.\n");
        open(my $cmakeFile, ">", "$fileName") or die "[ERR] Could not generate CMake with error: $!\n";
        
        write_cmake($cmakeFile, $test_name);
        close($cmakeFile);

        print("\n[INFO] Generate $fileName successfully.\n");
    }
}

sub gen_basedir() {
    my $base_dir = "src";
    my $build_dir = "$base_dir/build";
    my $cpp_main = "$base_dir/main.cc";

    if(! -d $base_dir) {
        print "Could not find $base_dir. Generate now...";
        make_path($build_dir) or die "Could not generate $base_dir & $build_dir $!\n";

        open(my $cpp_file, ">", $cpp_main) or die "[ERR] Could not generate C++ source with error: $!\n";
        gen_cpp_test($cpp_file);
        print "Generate C++ Test base successfully.\n";

        return $build_dir;
    }

    return $build_dir;
}

sub run_test {
    my $test_name="translator";
    my ($build_dir) = @_;

    chdir $build_dir or die "Could not change directory to: $build_dir with error: $!\n";

    my $cmake_rc = system("cmake", "../..");
    die "[ERR] CMake error" if $cmake_rc != 0;

    my $make_rc = system("make");
    die "[ERR] Makefile error" if $make_rc != 0;

    my $prorgam = system("./$test_name");
    die "[ERR] Test FAILED" if $prorgam != 0;
}

sub tool_check {
    my ($cmd) = @_;
    my $found = system("which $cmd > /dev/null 2>&1") == 0;

    return $found;
}

die "[ERR] Could not find CMake" unless tool_check("cmake");
die "[ERR] Could not find Clang" unless tool_check("clang");
die "[ERR] Could not find Make" unless tool_check("make");

# If CMakeLists.txt is not exists & base directory test is not exists.
gen_cmake();
my $build_dir = gen_basedir();
run_test($build_dir);

print("Test passed.\n")