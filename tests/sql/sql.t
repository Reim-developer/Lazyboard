#!/usr/bin/perl
use strict;
use warnings;
use lib "../test_lib";
use test_lib qw(gen_cmake gen_base_dir run_test);

# Gen CMakeLists.txt if it doesn't exists.
my $test_name = "sql_test";
my $base_source = <<END;
// Auto gen base test.
#include <sqlite3.h>
#include <stdio.h>
#define TEST_DB_NAME
int main() {
    sqlite3 *database;
    int result = sqlite3_open("zclipboard_test.db", &database);
    char *err_msg = NULL;

    if (result != SQLITE_OK) {
        printf("%s", sqlite3_errmsg(database));
        return 1;
    }

    const char *sql_query = R"(
         CREATE TABLE IF NOT EXISTS clipboard (
            time TEXT, content TEXT,
            content_hash TEXT PRIMARY KEY,
            length INTEGER,
            image_data BLOB,
            is_pinned INTEGER DEFAULT 0
        )
    )";
    const char *insert_query = R"(
        INSERT INTO clipboard (time, content, content_hash, length)
        VALUES ('2024-10-25 15:00:00', 'Hello SQLite!', 'abc123', 13)
    )";
    int result_1 = sqlite3_exec(database, sql_query, 0, 0, &err_msg);

    if (result_1 != SQLITE_OK) {
        printf("%s", err_msg);
        return 1;
    }

    sqlite3_exec(database, insert_query, 0, 0, 0);

    return 0;
}
END

my $base_cmake = <<'END';
cmake_minimum_required(VERSION 3.19)
project(sql_test)

set(CMAKE_C_STANDARD 99 REQUIRED)

set(SOURCES
    src/main.c
)

add_executable(${PROJECT_NAME} ${SOURCES})
find_package(PkgConfig REQUIRED)
pkg_check_modules(SQLITE3 REQUIRED IMPORTED_TARGET sqlite3)

target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::SQLITE3)
END

gen_cmake("$test_name", "$base_cmake");
my $build_dir = gen_base_dir("$base_source");
run_test("$build_dir", "$test_name");
print "Test passed."