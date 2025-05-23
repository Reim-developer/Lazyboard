// Auto gen base test.
#include <QtGlobal>
#include <cassert>

// clang-format off
enum class Platform : int { 
    LINUX, 
    WINDOWS, 
    MACOS, 
    UNKNOWN 
};

// clang-format on

int hasPlatform() {
    // clang-format off
    #ifdef Q_OS_LINUX
        return static_cast<int>(Platform::LINUX);
    #elif Q_OS_DARWIN
        return static_cast<int>(Platform::MACOS);
    #elif Q_OS_WINDOWS
        return static_cast<int>(Platform::WINDOWS);
    #else
        return static_cast<int>(Platform::UNKNOWN);
    #endif
    // clang-format on
}

int main() {
    int platform = hasPlatform();

    // clang-format off
    #ifdef Q_OS_LINUX
        assert(platform == static_cast<int>(Platform::LINUX));
    #elif Q_OS_DARWIN
        assert(platform == static_cast<int>(Platform::MACOS));
    #elif Q_OS_WINDOWS
        assert(platform static_cast<int>(Platform::WINDOWS));
    #else
        assert(platform static_cast<int>(Platform::UNKNOWN));
    #endif
    // clang-format on
}
