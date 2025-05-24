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
