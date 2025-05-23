#ifndef CORE_ENUM_HPP
#define CORE_ENUM_HPP

// clang-format off
namespace zclipboard::core {
    enum class Platform : int {
        LINUX,
        MACOS,
        WINDOWS,
        UNKNOWN
    };

    enum class ContentType : int {
        TEXT,
        IMAGE,
        UNKNOWN
    };

}  // namespace zclipboard::core

#endif  // CORE_ENUM_HPP