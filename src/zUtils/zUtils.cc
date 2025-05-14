#include "include/zUtils.hpp"
#include "include/settings.hpp"
#include <QtGlobal>
#include <QStandardPaths>
#include <QSettings>
#include <QClipboard>
#include <QApplication>
#include <QPointer>
#include <QMimeData>

using namespace zclipboard;

QString zUtils::getCachePath() {
#ifdef Q_OS_WIN
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
#else
    return QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
#endif
}

bool zUtils::getAutoHideSetting() {
    QSettings settings;
    return settings.value(AUTO_HIDE_SETTING, false).toBool();
}

bool zUtils::getAutoNotificationSetting() {
    QSettings settings;
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