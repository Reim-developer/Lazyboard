#ifndef SYSTEM_TRAY_HPP
#define SYSTEM_TRAY_HPP
#include <QSystemTrayIcon>
#include <QWidget>
#include <QObject>
#include <QMainWindow>
#include "../../core/include/systemTray.hpp"

using zclipboard::core::SystemTrayCore;

namespace zclipboard::zGui {

struct SystemTrayWidget {
    QMainWindow *window;
    QIcon icon;
};

class SystemTray : public QMainWindow {
    Q_OBJECT
   public:
    explicit SystemTray(QMainWindow *window);

    void addSystemTray(const SystemTrayWidget &widget);
    QSystemTrayIcon *getSystemTrayIcon();

   private:
    QMainWindow *window;
    SystemTrayCore *systemTrayCore;
    void translatorDectect(QMainWindow *window);

    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QAction *showGui;
    QAction *hideGui;
    QAction *quitGui;
};
}  // namespace zclipboard::zGui

#endif