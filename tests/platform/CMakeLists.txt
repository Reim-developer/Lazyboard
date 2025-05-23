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
