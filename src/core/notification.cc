#define QT_NO_KEYWORDS
#include <QtGlobal>

// clang-format off
#if defined(Q_OS_LINUX)
    #undef signals
    #include <glib-object.h>
    #include <libnotify/notification.h>
    #include <libnotify/notify.h>
    #include "include/embed_icon.hpp"
#endif
    #define signals Q_OBJECT_signals
// clang-format on

#include "include/enum.hpp"
#include "include/notification.hpp"
#include "../zUtils/include/config.hpp"
#include "../zUtils/include/zUtils.hpp"
#include "../language/include/translate.hpp"
#include "../language/include/language.hpp"
#include "../zUtils/include/settings.hpp"
#include <QSettings>

using zclipboard::core::NotificationCore;
using zclipboard::language::Translate;

void NotificationCore::onClipboardChanged(QSystemTrayIcon *trayIcon, QClipboard *clipboard) {
    connect(clipboard, &QClipboard::dataChanged, [this, trayIcon, clipboard]() {
        const QMimeData *mimeData = clipboard->mimeData();
        const QSettings settings(AUTHOR_NAME, APP_NAME);
        const auto LANGUAGE_TYPE = settings.value(LANGUAGE_SETTING).toInt();

        if (zUtils::getAutoNotificationSetting() && mimeData->hasText()) {
            // clang-format off
            #if defined(Q_OS_LINUX)
                if (zUtils::hasPlatform() == static_cast<int>(Platform::LINUX)) {
                    sendLinuxNotification(LANGUAGE_TYPE);
                    return;
                }
            #endif
            // clang-format on

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

// clang-format off
#if defined(Q_OS_LINUX)
    static GdkPixbuf *createPixbuf(const uint8_t *data, size_t length) {
        GdkPixbufLoader *loader = gdk_pixbuf_loader_new();
        gdk_pixbuf_loader_write(loader, data, length, nullptr);

        gdk_pixbuf_loader_close(loader, nullptr);

        GdkPixbuf *pixbuf = gdk_pixbuf_loader_get_pixbuf(loader);
        g_object_ref(pixbuf);

        g_object_unref(loader);
        return pixbuf;
    }


    void NotificationCore::sendLinuxNotification(const int &TYPE) {
        static bool initialized = false;

        if (!initialized) {
            notify_init(APP_NAME);
            initialized = true;
        }

        const char *title = nullptr;
        const char *body = nullptr;
        const constexpr int TIMEOUT = 5000;  // 5 MS.

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
        
        GdkPixbuf *pixbuf = createPixbuf(ICON_EMBED, ICON_EMBED_LEN);

        NotifyNotification *notification = notify_notification_new(title, body, nullptr);

        notify_notification_set_icon_from_pixbuf(notification, pixbuf);
        notify_notification_set_timeout(notification, TIMEOUT);
        notify_notification_show(notification, nullptr);

        g_object_unref(notification);
        g_object_unref(pixbuf);
}
#endif