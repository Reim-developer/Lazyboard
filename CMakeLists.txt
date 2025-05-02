cmake_minimum_required(VERSION 3.19)
project(zclipboard)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Qml)

set(CXX_SOURCE)
set(CXX_HEADER)
set(ASSETS resources.qrc)

file(GLOB_RECURSE SOURCES "src/*.cc")
file(GLOB_RECURSE HEADER_SOURCES "src/*.hpp")

foreach(SOURCE_FILE ${SOURCES})
    list(APPEND CXX_SOURCE ${SOURCE_FILE})
endforeach()

foreach(HEADER_FILE ${HEADER_SOURCES})
    list(APPEND CXX_HEADER ${HEADER_FILE})
endforeach()

qt_add_executable(${PROJECT_NAME} ${CXX_SOURCE} ${CXX_HEADER} ${ASSETS})

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE Qt6::Widgets
    PRIVATE Qt6::Gui
    PRIVATE yaml-cpp 
)

target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CXX_COMPILER_ID:Clang>:-fno-direct-access-external-data>")