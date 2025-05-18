#include "include/zwindow.hpp"
#include "include/clearButton.hpp"
#include "include/getButton.hpp"
#include "include/settingButton.hpp"
#include "include/ztable.hpp"
#include "include/zSearchPanel.hpp"
#include "../zUtils/include/zUtils.hpp"
#include "../zUtils/include/settings.hpp"
#include "../language/include/translate.hpp"
#include "include/disconnectButton.hpp"
#include "../zUtils/include/config.hpp"
#include "../language/include/language.hpp"
#include <QStringLiteral>
#include <QApplication>
#include <QSettings>

using zclipboard::language::Translate;
using zclipboard::zGui::DisconnectButton;
using zclipboard::zGui::GetButton;
using zclipboard::zGui::SearchArea;
using zclipboard::zGui::ZTable;
using zclipboard::zGui::ZWindow;

ZWindow::ZWindow(QWidget *zWindow) : QMainWindow(zWindow) {
    zIcon = QIcon(ICON_PATH);

    zCentralWidget = new QWidget(zWindow);
    zLayout = new QGridLayout(zCentralWidget);

    setCentralWidget(zCentralWidget);
    setWindowTitle(APP_NAME);

    resize(AppConfig::Z_WINDOW_WIDTH, AppConfig::Z_WINDOW_HEIGHT);
    setWindowIcon(zIcon);
    preloadTranslator();
    createTrayIcon();
    setupGui();
}

void ZWindow::createTrayIcon() {
    trayIcon = new QSystemTrayIcon(this);
    trayMenu = new QMenu();

    QAction *showGui = trayMenu->addAction(TRAY_SHOW_OPTION_EN);
    QAction *hideGui = trayMenu->addAction(TRAY_HIDE_OPTION_EN);
    QAction *quitGui = trayMenu->addAction(TRAY_QUIT_OPTION_EN);

    addTrayMenuActions(trayIcon);
    connect(showGui, &QAction::triggered, this, &ZWindow::showNormal);
    connect(quitGui, &QAction::triggered, this, &QApplication::quit);
    connect(hideGui, &QAction::triggered, this, &ZWindow::hide);

    trayIcon->setIcon(zIcon);
    trayIcon->setToolTip(TOOL_TIP_TEXT_EN);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}

void ZWindow::addTrayMenuActions(QSystemTrayIcon *trayIcon) {
    connect(trayIcon, &QSystemTrayIcon::activated,
            [this](QSystemTrayIcon::ActivationReason reason) {
                if (reason == QSystemTrayIcon::DoubleClick || reason == QSystemTrayIcon::Trigger) {
                    showNormal();
                    activateWindow();
                }
            });
}

void ZWindow::setupGui() {
    ztable = new ZTable();
    zSearchArea = new SearchArea();
    clearButton = new ClearButton();
    getButton = new GetButton();
    settingButton = new SettingButton();
    disconnectButton = new DisconnectButton();

    ztable->addZtable(this, zLayout);
    zSearchArea->addSearchPanel({.zWindow = this, .zLayout = zLayout, .table = ztable});
    clearButton->addClearButton(zLayout, ztable);
    getButton->addGetButton(this, zLayout);
    settingButton->addSettingButton(this, zLayout);
    disconnectButton->addDisconnectButton(
        {.parent = this, .layout = zLayout, .getButton = getButton});

    zUtils::textClipboardChanges(trayIcon, ztable->getClipboard());
    zUtils::imageClipboardChanges(trayIcon, ztable->getClipboard());
}

void ZWindow::closeEvent(QCloseEvent *event) {
    if (zUtils::getAutoHideSetting()) {
        hide();
        event->ignore();
    } else {
        event->accept();
    }
}

void ZWindow::preloadTranslator() {
    if (!zUtils::getLanguageSetting()) {
        QSettings settings(AUTHOR_NAME, APP_NAME);
        settings.setValue(LANGUAGE_SETTING, Translate::ENGLISH);

        return;
    }
}