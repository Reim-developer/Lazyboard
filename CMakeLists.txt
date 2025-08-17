cmake_minimum_required(VERSION 3.19)
project(Lazyboard)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)
find_package(SQLite3 REQUIRED)

set(RUST_BACKEND_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/back_end)

if(RELEASE)
    set(RUST_BACKEND_LIB ${RUST_BACKEND_DIR}/target/release/libback_end.a)

elseif(LAZY_DEBUG)
    add_compile_definitions(PRIVATE LAZY_DEBUG)
    set(RUST_BACKEND_LIB ${RUST_BACKEND_DIR}/target/debug/libback_end.a)
endif()


file(GLOB_RECURSE SOURCES_CXX "src/*.cxx")
file(GLOB_RECURSE SOURCES_C "src/*.c")
file(GLOB_RECURSE HEADER_SOURCES "src/*.h" "src/*.hxx")

add_custom_target(
    BuildRustBacked
    DEPENDS ${RUST_BACKEND_LIB}
)

qt_add_executable(${PROJECT_NAME} ${SOURCES_CXX} ${SOURCES_C} ${HEADER_SOURCES})
add_dependencies(${PROJECT_NAME} BuildRustBacked)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE Qt6::Widgets
    PRIVATE Qt6::Core
    PRIVATE Qt6::Gui
    PRIVATE SQLite::SQLite3
    PRIVATE ${RUST_BACKEND_LIB}
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CXX_COMPILER_ID:Clang>:-fno-direct-access-external-data>")
    set(CMAKE_CXX_CLANG_TIDY clang-tidy)
endif()

message(STATUS "Current C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Current C++ Compiler: ${CMAKE_CXX_COMPILER}")

install(TARGETS ${PROJECT_NAME} DESTINATION bin)