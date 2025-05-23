#include "include/systemTray.hpp"
#include "../language/include/language.hpp"
#include "../zUtils/include/zUtils.hpp"
#include "../zUtils/include/settings.hpp"
#include "../zUtils/include/config.hpp"
#include "../language/include/translate.hpp"
#include <QSettings>
#include <QMenu>
#include "include/zwindow.hpp"
#include <QApplication>
#include <QSystemTrayIcon>
#include <QAction>
#include "../core/include/systemTray.hpp"

using zclipboard::core::SystemTrayCore;
using zclipboard::core::SystemTrayParams;
using zclipboard::language::Translate;
using zclipboard::zGui::SystemTray;
using zclipboard::zGui::SystemTrayWidget;

SystemTray::SystemTray(QMainWindow *mainWindow) : window(mainWindow) {}

void SystemTray::addSystemTray(const SystemTrayWidget &widget) {
    trayIcon = new QSystemTrayIcon(widget.window);
    trayMenu = new QMenu();
    systemTrayCore = new SystemTrayCore();
    QSettings setting(AUTHOR_NAME, APP_NAME);

    const auto TYPE = setting.value(LANGUAGE_SETTING).toInt();

    // clang-format off
    struct SystemTrayParams systemTrayParams {
            .trayMenu = trayMenu,
            .window = window,
            .TYPE = TYPE
    };
    // clang-format on

    systemTrayCore->updateSwitchLanguageInstance(systemTrayParams);
    translatorDectect(widget.window);

    trayIcon->setIcon(widget.icon);
    trayIcon->setToolTip(TOOL_TIP_TEXT_EN);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}

void SystemTray::translatorDectect(QMainWindow *window) {
    QSettings *settings = new QSettings(AUTHOR_NAME, APP_NAME);
    if (!zUtils::getLanguageSetting()) {
        settings->setValue(LANGUAGE_SETTING, Translate::ENGLISH);
    }

    const int TYPE = settings->value(LANGUAGE_SETTING).toInt();

    // clang-format off
    struct SystemTrayParams systemTrayParams {
        .trayMenu = trayMenu,
        .window = window,
        .TYPE = TYPE
    };
    // clang-format on

    systemTrayCore->loadTranslator(systemTrayParams);
}

QSystemTrayIcon *SystemTray::getSystemTrayIcon() {
    return trayIcon;
}