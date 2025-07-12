#include <QtGlobal>
#include "./C_Lib/Include/Notification.h"
#include "Include/CoreNotification.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Utils/Include/Utils.hpp"
#include "../Language/Include/Translate.hpp"
#include "../Language/Include/Language.hpp"
#include "../Utils/Include/Settings.hpp"
#include <QSettings>

using ZClipboard::Core::NotificationCore;
using ZClipboard::Language::Translate;
using ZClipboard::AppUtils::Utils;

void NotificationCore::onClipboardChanged(QSystemTrayIcon *trayIcon, QClipboard *clipboard) {
    const auto functionNotification = [this, trayIcon, clipboard]() {
        const QMimeData *mimeData = clipboard->mimeData();
        const QSettings settings(AUTHOR_NAME, APP_NAME);
        const auto LANGUAGE_TYPE = settings.value(LANGUAGE_SETTING).toInt();

        if (Utils::hasSetting(AUTO_NOTIFICATION_SETTING)) {
            if (Utils::hasContentType(mimeData) == ContentType::TEXT) {

                // clang-format off
                #if defined(Q_OS_LINUX)
                    if (Utils::hasPlatform() == Platform::LINUX) {
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