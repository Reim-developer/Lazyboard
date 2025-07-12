#ifndef SYSTEM_TRAY_HPP
#define SYSTEM_TRAY_HPP
#include <QSystemTrayIcon>
#include <QWidget>
#include <QObject>
#include <QMainWindow>
#include "../../Core/Include/CoreSystemTray.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"

using ZClipboard::Core::SystemTrayCore;

GUI_NAMESPACE

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

        QSystemTrayIcon *trayIcon;
        QMenu *trayMenu;
        QAction *showGui;
        QAction *hideGui;
        QAction *quitGui;
    };

END_NAMESPACE
#endif