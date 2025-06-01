import os
from MikotoTest import MikotoTest

def main() -> None:
    TEST_NAME: str = "./encryption_test"
    mikotoTest = MikotoTest()

    build: str = "encrypt/src/build"

    if not os.path.exists("encrypt/src"):

        CMake_URL: str = "https://raw.githubusercontent.com/Reim-developer/zClipboard/refs/heads/master/tests/encrypt/CMakeLists.txt"
        CXX_Main_URL: str = "https://github.com/Reim-developer/zClipboard/raw/refs/heads/master/tests/encrypt/src/main.cc"
        C_Lib_URL: str = "https://github.com/Reim-developer/zClipboard/raw/refs/heads/master/tests/encrypt/src/lib/encrypt.c"
        C_Header_URL: str = "https://github.com/Reim-developer/zClipboard/raw/refs/heads/master/tests/encrypt/src/lib/include/encrypt.h"

        src = mikotoTest.mkdirProject(path = "encrypt/src")
        build = mikotoTest.mkdirProject(path = "encrypt/src/build")
        lib = mikotoTest.mkdirProject(path = "encrypt/src/lib")
        lib_include = mikotoTest.mkdirProject(path = "encrypt/src/lib/include")

        CMake_Source = mikotoTest.getRawCodeFromGitHub(raw_url = CMake_URL)
        CXX_Main_Source = mikotoTest.getRawCodeFromGitHub(raw_url = CXX_Main_URL)
        C_Lib_Source = mikotoTest.getRawCodeFromGitHub(raw_url = C_Lib_URL)
        C_Header_Source = mikotoTest.getRawCodeFromGitHub(raw_url = C_Header_URL)

        CMake_Location = f"{mikotoTest.getCwd()}/{mikotoTest.getFileNameFromURL(CMake_URL)}"
        CXX_Main_Location = f"{src}/{mikotoTest.getFileNameFromURL(CXX_Main_URL)}"
        C_Lib_Location = f"{lib}/{mikotoTest.getFileNameFromURL(C_Lib_URL)}"
        C_Header_Location = f"{lib_include}/{mikotoTest.getFileNameFromURL(C_Header_URL)}"

        if CMake_Source:
            mikotoTest.writeRawCodeTo(path = CMake_Location, raw_content = CMake_Source)

        if CXX_Main_Source:
            mikotoTest.writeRawCodeTo(path = CXX_Main_Location, raw_content = CXX_Main_Source)

        if C_Lib_Source:
            mikotoTest.writeRawCodeTo(path = C_Lib_Location, raw_content = C_Lib_Source)

        if C_Header_Source:
            mikotoTest.writeRawCodeTo(path = C_Header_Location, raw_content = C_Header_Source)


    mikotoTest.run_program(
        ["cmake", "../.."],
        build
    )
    mikotoTest.run_program(
        "make",
        build
    )
    mikotoTest.run_program(
        TEST_NAME,
        build, verbose = True
    )


main()
