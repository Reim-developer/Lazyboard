#include "Include/SystemTray.hpp"
#include "../Language/Include/Language.hpp"
#include "../Utils/Include/Settings.hpp"
#include "../Utils/Include/Config.hpp"
#include <QSettings>
#include <QMenu>
#include "Include/Window.hpp"
#include <QApplication>
#include <QSystemTrayIcon>
#include <QAction>
#include "../Core/Include/CoreSystemTray.hpp"

using ZClipboard::Core::SystemTrayCore;
using ZClipboard::Core::SystemTrayParams;
using ZClipboard::GUI::SystemTray;
using ZClipboard::GUI::SystemTrayWidget;

SystemTray::SystemTray(QMainWindow *mainWindow) : window(mainWindow) {}

void SystemTray::addSystemTray(const SystemTrayWidget &widget) {
    trayIcon = new QSystemTrayIcon(widget.window);
    trayMenu = new QMenu();
    systemTrayCore = new SystemTrayCore();
    QSettings *setting = new QSettings(AUTHOR_NAME, APP_NAME);

    const auto TYPE = setting->value(LANGUAGE_SETTING).toInt();

    // clang-format off
    struct SystemTrayParams systemTrayParams {
            .window = window,
            .settings = setting,
            .trayMenu = trayMenu,
            .TYPE = TYPE
    };
    // clang-format on

    systemTrayCore->translatorDectect(systemTrayParams);
    systemTrayCore->updateSwitchLanguageInstance(systemTrayParams);

    trayIcon->setIcon(widget.icon);
    trayIcon->setToolTip(TOOL_TIP_TEXT_EN);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}

QSystemTrayIcon *SystemTray::getSystemTrayIcon() {
    return trayIcon;
}