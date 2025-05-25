#!/usr/bin/perl
use strict;
use warnings;
use lib "../test_lib";
use test_lib qw(gen_cmake gen_base_dir run_test);

# Gen CMakeLists.txt if it doesn't exists.
my $test_name = "setting_qt";
my $base_source = <<END;
// Auto gen base test.
#include <QSettings>
#include <QDebug>
#include "../../../src/zUtils/include/settings.hpp"

int main() {
    QSettings *settings = new QSettings("ReimEmp", "zClipboard");
    if (!settings->contains(LANGUAGE_SETTING)) {
        qDebug() << "Key: " << LANGUAGE_SETTING << " doesn't exists.";
        return 1;
    }

    qDebug() << settings->value(LANGUAGE_SETTING).toInt();
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
my $c_type = "cc"
my $build_dir = gen_base_dir("$base_source", "$c_type");
run_test("$build_dir", "$test_name");
print "Test passed."