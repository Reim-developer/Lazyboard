#include "include/zUtils.hpp"
#include "include/settings.hpp"
#include "include/config.hpp"
#include <QtGlobal>
#include <QStandardPaths>
#include <QSettings>
#include <QClipboard>
#include <QApplication>
#include <QPointer>
#include <QMimeData>
#include "../language/include/translate.hpp"

using namespace zclipboard;
using zclipboard::language::Translate;

QString zUtils::getCachePath() {
#ifdef Q_OS_WIN
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
#else
    return QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
#endif
}

bool zUtils::getAutoHideSetting() {
    QSettings settings(AUTHOR_NAME, APP_NAME);
    return settings.value(AUTO_HIDE_SETTING, false).toBool();
}

bool zUtils::getAutoNotificationSetting() {
    QSettings settings(AUTHOR_NAME, APP_NAME);
    return settings.value(AUTO_NOTIFICATION_SETTING, false).toBool();
}

void zUtils::textClipboardChanges(QSystemTrayIcon *trayIcon, QClipboard *clipboard) {
    connect(clipboard, &QClipboard::dataChanged, [trayIcon, clipboard]() {
        const QMimeData *mimeData = clipboard->mimeData();

        if (getAutoNotificationSetting() && mimeData->hasText()) {
            trayIcon->showMessage("Clipboard updated",
                                  "New text content has been copied to your clipboard.",
                                  QSystemTrayIcon::Information, 5000);
        }
    });
}

void zUtils::imageClipboardChanges(QSystemTrayIcon *trayIcon, QClipboard *clipboard) {
    connect(clipboard, &QClipboard::dataChanged, [trayIcon, clipboard]() {
        const QMimeData *mimeData = clipboard->mimeData();
        if (getAutoNotificationSetting() && mimeData->hasImage()) {
            trayIcon->showMessage("Clipboard updated",
                                  "New image has been copied to your clipboard.",
                                  QSystemTrayIcon::Information, 5000);
        }
    });
}

bool zUtils::getLanguageSetting() {
    QSettings settings(AUTHOR_NAME, APP_NAME);
    return settings.contains(LANGUAGE_SETTING);
}

Translate::LanguageType zUtils::languageTypeCast(int value) {
    QSettings settings(AUTHOR_NAME, APP_NAME);
    return static_cast<Translate::LanguageType>(settings.value(LANGUAGE_SETTING).toInt());
}