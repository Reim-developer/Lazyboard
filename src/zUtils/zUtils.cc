#include <QtGlobal>
#include "include/zUtils.hpp"
#include "include/settings.hpp"
#include "include/config.hpp"
#include <QStandardPaths>
#include <QSettings>
#include <QClipboard>
#include <QApplication>
#include <QPointer>
#include <QMimeData>
#include "../language/include/translate.hpp"
#include <QApplication>
#include <QStyleFactory>

using namespace zclipboard;
using zclipboard::core::ContentType;
using zclipboard::core::Platform;
using zclipboard::language::Translate;

QString zUtils::getCachePath() {
    switch (hasPlatform()) {
        case Platform::LINUX:
            return QStandardPaths::writableLocation(QStandardPaths::CacheLocation);

        case Platform::MACOS:
            return QStandardPaths::writableLocation(QStandardPaths::CacheLocation);

        case Platform::WINDOWS:
            return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);

        // Unknown operating system.
        default:
            return QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    }
}

/*
* Test from: tests/platform.
*/
Platform zUtils::hasPlatform() {
    // clang-format off
    #if defined(Q_OS_LINUX)
        return Platform::LINUX;
    #elif defined(Q_OS_MACOS)
        return Platform::MACOS;
    #elif defined(Q_OS_WINDOWS)
        return Platform::WINDOWS;
    #else
        return Platform::UNKNOWN;
    #endif
    // clang-format on
}

bool zUtils::hasSetting(const char *SETTING_NAME) {
    QSettings settings(AUTHOR_NAME, APP_NAME);
    return settings.value(SETTING_NAME).toBool();
}

Translate::LanguageType zUtils::languageTypeCast(int value) {
    QSettings settings(AUTHOR_NAME, APP_NAME);
    return static_cast<Translate::LanguageType>(settings.value(LANGUAGE_SETTING).toInt());
}

int zUtils::hasContentType(const QMimeData *mimeData) {
    if (mimeData->hasText()) return static_cast<int>(ContentType::TEXT);
    if (mimeData->hasImage()) return static_cast<int>(ContentType::IMAGE);

    return static_cast<int>(ContentType::UNKNOWN);
}
