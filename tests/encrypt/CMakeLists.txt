cmake_minimum_required(VERSION 3.19)
project(encryption_test)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED IMPORTED_TARGET libsodium)


file(GLOB_RECURSE CXX_SRC "src/*.cc")
file(GLOB_RECURSE C_SRC "src/lib/*.c")
file(GLOB_RECURSE HEADER "src/*.h" "src/*.hpp")

add_executable(${PROJECT_NAME} ${CXX_SRC} ${C_SRC} ${HEADER})

target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::SODIUM)