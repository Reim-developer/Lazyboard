#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#include <QSystemTrayIcon>
#include "../../Utils/Include/Namespace_Macro.hpp"
#include <QClipboard>

CORE_NAMESPACE

    class NotificationCore : public QObject {
        Q_OBJECT

    public:
            #if defined(Q_OS_LINUX)
                void notificationTranslator(const int &TYPE);
            #endif

            void sendNotification(const int &TYPE, QSystemTrayIcon *trayIcon);
            void onClipboardChanged(QSystemTrayIcon *trayIcon, QClipboard *clipboard);
    };
    
END_NAMESPACE

#endif  // NOTIFICATION_HPP