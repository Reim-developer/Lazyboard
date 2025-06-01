cmake_minimum_required(VERSION 3.19)
project(zClipboard)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Gui Core Network)
find_package(PkgConfig REQUIRED)

if(LINUX)
    pkg_check_modules(LIBNOTIFY REQUIRED IMPORTED_TARGET libnotify)
endif()

if(NOT WIN32)
    pkg_check_modules(SODIUM REQUIRED IMPORTED_TARGET libsodium)
endif()

set(CXX_SOURCE)
set(CXX_HEADER)
set(ASSETS resources.qrc)

file(GLOB_RECURSE SOURCES_CXX "src/*.cc")
file(GLOB_RECURSE SOURCES_C "src/*.c")
file(GLOB_RECURSE HEADER_SOURCES "src/*.h" "src/*.hpp")

qt_add_executable(${PROJECT_NAME} ${SOURCES_CXX} ${SOURCES_C} ${HEADER_SOURCES} ${ASSETS})

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE Qt6::Widgets
    PRIVATE Qt6::Sql
    PRIVATE Qt6::Core
    PRIVATE Qt6::Gui
    PRIVATE Qt6::Network
)
if(Z_DEBUG)
    add_compile_definitions(${PROJECT_NAME} PRIVATE Z_DEBUG)
endif()

if(NOT WIN32) 
    target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::SODIUM)
endif()

if(WIN32)
    find_package(sodium CONFIG REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE sodium)
endif()

if(LINUX)
    target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::LIBNOTIFY)
endif()

if(NOT WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE -lstdc++)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CXX_COMPILER_ID:Clang>:-fno-direct-access-external-data>")
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)