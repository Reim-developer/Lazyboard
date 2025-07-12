#include <QtGlobal>
#include "Include/Utils.hpp"
#include "Include/Settings.hpp"
#include "Include/Config.hpp"
#include <QStandardPaths>
#include <QSettings>
#include <QClipboard>
#include <QApplication>
#include <QPointer>
#include <QMimeData>
#include "../Language/Include/Translate.hpp"
#include <QApplication>
#include <QStyleFactory>


using ZClipboard::Core::ContentType;
using ZClipboard::Core::Platform;
using ZClipboard::Language::Translate;
using ZClipboard::AppUtils::Utils;

QString Utils::getCachePath() {
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
Platform Utils::hasPlatform() {
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

bool Utils::hasSetting(const char *SETTING_NAME) {
    QSettings settings(AUTHOR_NAME, APP_NAME);
    return settings.contains(SETTING_NAME);
}

Translate::LanguageType Utils::languageTypeCast(int value) {
    QSettings settings(AUTHOR_NAME, APP_NAME);
    return static_cast<Translate::LanguageType>(settings.value(LANGUAGE_SETTING).toInt());
}

ContentType Utils::hasContentType(const QMimeData *mimeData) {
    if (mimeData->hasText()) return ContentType::TEXT;
    if (mimeData->hasImage()) return ContentType::IMAGE;

    return ContentType::UNKNOWN;
}