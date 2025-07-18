cmake_minimum_required(VERSION 3.19)
project(nullptrassert)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES_CXX "Source/*.cc")
add_executable(${PROJECT_NAME} ${SOURCES_CXX})

if(Z_DEBUG)
    message(STATUS "Debug mode is enabled.")
endif()

if(Z_DEBUG)
    add_compile_definitions(${PROJECT_NAME} PRIVATE Z_DEBUG)
endif()

# We suggest use Clang for compiler.
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CXX_COMPILER_ID:Clang>:-fno-direct-access-external-data>")
    # Warning:
    # Only enable when use
    # -DZ_DEBUG=1.
    # We will disable it in default, for ABI mismatch reason.
    if(Z_DEBUG)
        add_compile_options(-stdlib=libc++)
        target_link_libraries(${PROJECT_NAME} PRIVATE -lc++ -lc++abi)
    endif()
endif()