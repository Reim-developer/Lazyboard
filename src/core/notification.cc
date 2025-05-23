#include "include/enum.hpp"
#define QT_NO_KEYWORDS
#include <glib-object.h>
#include <libnotify/notification.h>
#include "include/notification.hpp"
#include "../zUtils/include/config.hpp"
#include "../zUtils/include/zUtils.hpp"
#include "../language/include/translate.hpp"
#include "../language/include/language.hpp"
#include "../zUtils/include/settings.hpp"
#include <libnotify/notify.h>
#include <QString>
#include <QSettings>

using zclipboard::core::NotificationCore;
using zclipboard::language::Translate;

void NotificationCore::onClipboardChanged(QSystemTrayIcon *trayIcon, QClipboard *clipboard) {
    connect(clipboard, &QClipboard::dataChanged, [this, trayIcon, clipboard]() {
        const QMimeData *mimeData = clipboard->mimeData();
        const QSettings settings(AUTHOR_NAME, APP_NAME);
        const auto LANGUAGE_TYPE = settings.value(LANGUAGE_SETTING).toInt();

        if (zUtils::getAutoNotificationSetting() && mimeData->hasText()) {
            if (zUtils::hasPlatform() == static_cast<int>(Platform::LINUX)) {
                sendLinuxNotification(LANGUAGE_TYPE);
                return;
            }

            sendNotification(LANGUAGE_TYPE, trayIcon);
        }
    });
}

void NotificationCore::sendNotification(const int &TYPE, QSystemTrayIcon *trayIcon) {
    const char *title = nullptr;
    const char *body = nullptr;

    switch (static_cast<Translate::LanguageType>(TYPE)) {
        case Translate::ENGLISH:
            title = CLIPBOARD_CHANGED_TITLE_EN;
            body = CLIPBOARD_CHANGED_TEXT_EN;
            break;

        case Translate::VIETNAMESE:
            title = CLIPBOARD_CHANGED_TITLE_VI;
            body = CLIPBOARD_CHANGED_TEXT_VI;
            break;
    }

    trayIcon->showMessage(title, body, QSystemTrayIcon::Information, 5000);
}

void NotificationCore::sendLinuxNotification(const int &TYPE) {
    static bool initialized = false;

    if (!initialized) {
        notify_init(APP_NAME);
        initialized = true;
    }

    const char *title = nullptr;
    const char *body = nullptr;

    switch (static_cast<Translate::LanguageType>(TYPE)) {
        case Translate::VIETNAMESE:
            title = CLIPBOARD_CHANGED_TITLE_VI;
            body = CLIPBOARD_CHANGED_TEXT_VI;
            break;

        case Translate::ENGLISH:
            title = CLIPBOARD_CHANGED_TITLE_EN;
            body = CLIPBOARD_CHANGED_TEXT_EN;
            break;
    }

    NotifyNotification *notification = notify_notification_new(title, body, nullptr);
    notify_notification_show(notification, nullptr);
    g_object_unref(notification);
}