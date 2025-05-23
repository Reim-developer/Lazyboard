#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP
#include <QSystemTrayIcon>
#include <QClipboard>

namespace zclipboard::core {
class NotificationCore : public QObject {
    Q_OBJECT

   public:
    void sendLinuxNotification(const int &TYPE);
    void sendNotification(const int &TYPE, QSystemTrayIcon *trayIcon);
    void onClipboardChanged(QSystemTrayIcon *trayIcon, QClipboard *clipboard);
};
}  // namespace zclipboard::core

#endif  // NOTIFICATION_HPP