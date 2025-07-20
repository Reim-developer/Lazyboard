#ifndef SYSTEM_TRAY_HPP
#define SYSTEM_TRAY_HPP
#include <QSystemTrayIcon>
#include <QWidget>
#include <QObject>
#include <QMainWindow>
#include "../../Core/Include/CoreSystemTray.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../Toolkit/Include/MainWindow_Components.hpp"

using ZClipboard::Core::SystemTrayCore;
using ZClipboard::GUI::Toolkit::ComponentsToolkit;

GUI_NAMESPACE
    class SystemTray {

    private:
        using Toolkit = ComponentsToolkit;
        using Window = QMainWindow;

    public:
        void SetupSystemTray(Window *window, QIcon *icon, Toolkit *toolkit);

    private:
        SystemTrayCore *systemTrayCore;
    };

END_NAMESPACE
#endif