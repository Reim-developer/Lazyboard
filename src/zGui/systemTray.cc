#include "include/systemTray.hpp"
#include "../language/include/language.hpp"
#include "../zUtils/include/settings.hpp"
#include "../zUtils/include/config.hpp"
#include <QSettings>
#include <QMenu>
#include "include/zwindow.hpp"
#include <QApplication>
#include <QSystemTrayIcon>
#include <QAction>
#include "../core/include/systemTray.hpp"

using zclipboard::core::SystemTrayCore;
using zclipboard::core::SystemTrayParams;
using zclipboard::zGui::SystemTray;
using zclipboard::zGui::SystemTrayWidget;

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