#include <QtGlobal>
#include "include/enum.hpp"
#include "./c/include/notification.h"
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
    const auto functionNotification = [this, trayIcon, clipboard]() {
        const QMimeData *mimeData = clipboard->mimeData();
        const QSettings settings(AUTHOR_NAME, APP_NAME);
        const auto LANGUAGE_TYPE = settings.value(LANGUAGE_SETTING).toInt();

        if (zUtils::hasSetting(AUTO_NOTIFICATION_SETTING)) {
            if (zUtils::hasContentType(mimeData) == ContentType::TEXT) {

                // clang-format off
                #if defined(Q_OS_LINUX)
                    if (zUtils::hasPlatform() == Platform::LINUX) {
                        notificationTranslator(LANGUAGE_TYPE);
                        return;
                    }
                #endif
                // clang-format on

                sendNotification(LANGUAGE_TYPE, trayIcon);
            }
        }
    };

    connect(clipboard, &QClipboard::dataChanged, functionNotification);
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
    void NotificationCore::notificationTranslator(const int &TYPE) {   
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
        
      sendLinuxNotification(title, body);
}
#endif