"""
zClipboard Project.
Test case: encrypt.
"""
import os
import sys
import logging
import subprocess
import shutil

logging.basicConfig(
    level = logging.INFO,
    format = "[%(asctime)s] [%(levelname)s] %(message)s",
    datefmt = "%Y-%m-%d %H:%M:%S"
)

try:
    import requests
except ModuleNotFoundError:
    logging.critical("Missing module requests. Are you missing installing it?")
    sys.exit(1)

# Project structure, status code base.
SRC_BASE: str = "src"
LIB_BASE: str = "lib"
BUILD_BASE: str = "build"
INCLUDE_BASE: str = "include"
STATUS_OK: int = 200

def die(ERROR_URL: str, STATUS_CODE: int) -> None:
    logging.critical("Could not create GET request to:")
    logging.critical(f"[x] {ERROR_URL}")
    logging.critical(f"Status Code: {STATUS_CODE}")

    sys.exit(1)

def tools_check() -> None:
    clang: str | None = shutil.which("clang")
    cmake: str | None = shutil.which("cmake")
    make: str | None = shutil.which("make")

    missing_tools: list[str] = []

    if not clang:
        missing_tools.append("Clang")
    
    if not cmake:
        missing_tools.append("CMake")

    if not make:
        missing_tools.append("Make")
    
    if missing_tools:
        logging.critical(f"Could not find tool: {', '.join(missing_tools)}")
        sys.exit(1)

def gen_project_structure() -> None:

    os.mkdir(SRC_BASE)
    logging.info(f"Gen {SRC_BASE} successfully.")

    os.mkdir(f"{SRC_BASE}/{LIB_BASE}")
    logging.info(f"Gen project library ({SRC_BASE}/{LIB_BASE}) successfully.")

    os.mkdir(f"{SRC_BASE}/{LIB_BASE}/{INCLUDE_BASE}")
    logging.info(f"Gen project include structure ({SRC_BASE}/{LIB_BASE}/{INCLUDE_BASE}) successfully")

    os.mkdir(f"{SRC_BASE}/{BUILD_BASE}")
    logging.info(f"Gen project build dir ({SRC_BASE}/{BUILD_BASE}) successfully")


def gen_cmake() -> None:
    CMAKE_SOURCE_URL: str = "https://raw.githubusercontent.com/Reim-developer/zClipboard/refs/heads/master/tests/encrypt/CMakeLists.txt"
    CMAKE_FILE: str = os.path.basename(CMAKE_SOURCE_URL)

    response = requests.get(CMAKE_SOURCE_URL)

    if response.status_code != STATUS_OK:
        die(ERROR_URL = CMAKE_SOURCE_URL, STATUS_CODE = response.status_code)

    CMAKE_SOURCE = response.text
    logging.info("Found CMake source..")
 
    with open(file = f"{SRC_BASE}/{CMAKE_FILE}", mode = "w", encoding = "utf-8") as CMakeFile:
        CMakeFile.write(CMAKE_SOURCE)

    logging.info("Generate CMake source successfully.")

def gen_cxx_main() -> None:
    CXX_SOURCE_URL: str = "https://raw.githubusercontent.com/Reim-developer/zClipboard/refs/heads/master/tests/encrypt/src/main.cc"
    CXX_MAIN_FILE: str = os.path.basename(CXX_SOURCE_URL)

    response = requests.get(CXX_SOURCE_URL)

    if response.status_code != STATUS_OK:
        die(ERROR_URL = CXX_SOURCE_URL, STATUS_CODE = response.status_code)
    
    CXX_MAIN_SOURCE: str = response.text
    logging.info("Found CXX main source..")

    with open(file = f"{SRC_BASE}/{CXX_MAIN_FILE}", mode = "w", encoding = "utf-8") as CXX_Source:
        CXX_Source.write(CXX_MAIN_SOURCE)

    logging.info("Generate CXX main source successfully")

def gen_lib_test() -> None:
    LIB_C_URL: str = "https://raw.githubusercontent.com/Reim-developer/zClipboard/refs/heads/master/tests/encrypt/src/lib/encrypt.c"
    LIB_HEADER_URL: str = "https://raw.githubusercontent.com/Reim-developer/zClipboard/refs/heads/master/tests/encrypt/src/lib/include/encrypt.h"

    LIB_C_FILE: str = os.path.basename(LIB_C_URL)
    LIB_C_HEADER_FILE: str = os.path.basename(LIB_HEADER_URL)

    lib_c_response = requests.get(LIB_C_URL)
    lib_header_response = requests.get(LIB_HEADER_URL)

    if lib_c_response.status_code != STATUS_OK:
        die(ERROR_URL = LIB_C_URL, STATUS_CODE = lib_c_response.status_code)

    if lib_header_response.status_code != STATUS_OK:
        die(ERROR_URL = LIB_HEADER_URL, STATUS_CODE = lib_header_response.status_code)
    
    LIB_C_SOURCE: str = lib_c_response.text
    LIB_HEADER_SOURCE: str = lib_header_response.text

    with open(file = f"{SRC_BASE}/{LIB_BASE}/{INCLUDE_BASE}/{LIB_C_HEADER_FILE}", mode = "w", encoding = "utf-8") as C_Header:
        C_Header.write(LIB_HEADER_SOURCE)

    logging.info(f"Generate C library header successfully as {SRC_BASE}/{LIB_BASE}/{INCLUDE_BASE}/{LIB_C_HEADER_FILE}")

    with open(file = f"{SRC_BASE}/{LIB_BASE}/{LIB_C_FILE}", mode = "w", encoding = "utf-8") as C_Source:
        C_Source.write(LIB_C_SOURCE)

    logging.info(f"Generate C library source successfully as {SRC_BASE}/{LIB_BASE}/{LIB_C_FILE}")

def main():
    # Gen  project structure if not exists.
    if not os.path.exists(SRC_BASE):
        gen_project_structure()
        gen_cmake()
        gen_cxx_main()
        gen_lib_test()

    tools_check()
    
    BUILD_CWD = f"{SRC_BASE}/{BUILD_BASE}"
    PROGRAM_NAME = "./encryption_test"
    subprocess.run (
        ["cmake", "../.."],
        cwd = BUILD_CWD
    )
    subprocess.run (
        "make",
        cwd = BUILD_CWD
    )
    subprocess.run(
        f"{PROGRAM_NAME}",
        cwd = BUILD_CWD
    )

main()