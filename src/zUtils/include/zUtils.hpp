#ifndef Z_UTILS_HPP
#define Z_UTILS_HPP
#include <QString>
#include <QSystemTrayIcon>
#include <QWidget>
#include <QObject>

namespace zclipboard {
class zUtils : public QObject {
    Q_OBJECT

   public:
    static QString getCachePath();
    static bool getAutoHideSetting();
    static bool getAutoNotificationSetting();
    static void textClipboardChanges(QSystemTrayIcon *trayIcon, QClipboard *clipboard);
    static void imageClipboardChanges(QSystemTrayIcon *trayIcon, QClipboard *clipboard);
};
}  // namespace zclipboard

#endif