#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#include <QSystemTrayIcon>
#include <QClipboard>

namespace zclipboard::core {
class NotificationCore : public QObject {
    Q_OBJECT

   public:
    // clang-format off
    #if defined(Q_OS_LINUX)
        void notificationTranslator(const int &TYPE);
    #endif
    // clang-format on
    void sendNotification(const int &TYPE, QSystemTrayIcon *trayIcon);
    void onClipboardChanged(QSystemTrayIcon *trayIcon, QClipboard *clipboard);
};
}  // namespace zclipboard::core

#endif  // NOTIFICATION_HPP