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

    enum class Theme : int {
        SYSTEM,
        DARK,
        LIGHT
    };

    enum class HashState : int {
        HASH_OK,
        DELETED,
        MODIFIED,
    };

    enum class LoginState : int {
        LOGIN_OK,
        LOGIN_NOT_SET,
        LOGIN_FAILED
    };

}  // namespace zclipboard::core

#endif  // CORE_ENUM_HPP