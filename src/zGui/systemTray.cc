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
#include "include/LanguageManager.hpp"

using zclipboard::language::Translate;
using zclipboard::zGui::SystemTray;
using zclipboard::zGui::SystemTrayWidget;

SystemTray::SystemTray(QMainWindow *mainWindow) : window(mainWindow) {}

void SystemTray::addSystemTray(const SystemTrayWidget &widget) {
    trayIcon = new QSystemTrayIcon(widget.window);
    trayMenu = new QMenu();

    // clang-format off
    connect(&LanguageManager::instance(), &LanguageManager::languageChanged, this, &SystemTray::loadTranslator);
    // clang-format on

    translatorDectect(widget.window);

    trayIcon->setIcon(widget.icon);
    trayIcon->setToolTip(TOOL_TIP_TEXT_EN);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}

void SystemTray::addTrayMenuActions(QSystemTrayIcon *trayIcon) {
    connect(trayIcon, &QSystemTrayIcon::activated,
            [this](QSystemTrayIcon::ActivationReason reason) {
                if (reason == QSystemTrayIcon::DoubleClick || reason == QSystemTrayIcon::Trigger) {
                    showNormal();
                    activateWindow();
                }
            });
}

void SystemTray::translatorDectect(QMainWindow *window) {
    QSettings *settings = new QSettings(AUTHOR_NAME, APP_NAME);
    if (!zUtils::getLanguageSetting()) {
        settings->setValue(LANGUAGE_SETTING, Translate::ENGLISH);
        loadTranslator(Translate::ENGLISH);
        return;
    }

    const int TYPE = settings->value(LANGUAGE_SETTING).toInt();
    loadTranslator(TYPE);
}

void SystemTray::loadTranslator(const int &TYPE) {
    trayMenu->clear();

    switch (TYPE) {
        case Translate::ENGLISH:
            showGui = trayMenu->addAction(TRAY_SHOW_OPTION_EN);
            hideGui = trayMenu->addAction(TRAY_HIDE_OPTION_EN);
            quitGui = trayMenu->addAction(TRAY_QUIT_OPTION_EN);

            addTrayMenuActions(trayIcon);
            connect(showGui, &QAction::triggered, window, &ZWindow::showNormal);
            connect(quitGui, &QAction::triggered, window, &QApplication::quit);
            connect(hideGui, &QAction::triggered, window, &ZWindow::hide);
            break;

        case Translate::VIETNAMESE:
            showGui = trayMenu->addAction(TRAY_SHOW_OPTION_VI);
            hideGui = trayMenu->addAction(TRAY_HIDE_OPTION_VI);
            quitGui = trayMenu->addAction(TRAY_QUIT_OPTION_VI);

            addTrayMenuActions(trayIcon);
            connect(showGui, &QAction::triggered, window, &ZWindow::showNormal);
            connect(quitGui, &QAction::triggered, window, &QApplication::quit);
            connect(hideGui, &QAction::triggered, window, &ZWindow::hide);
            break;
    }
}

QSystemTrayIcon *SystemTray::getSystemTrayIcon() {
    return trayIcon;
}