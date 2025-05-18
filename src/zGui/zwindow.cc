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
#include "include/systemTray.hpp"
#include <QStringLiteral>
#include <QApplication>
#include <QSettings>

using zclipboard::language::Translate;
using zclipboard::zGui::DisconnectButton;
using zclipboard::zGui::GetButton;
using zclipboard::zGui::SearchArea;
using zclipboard::zGui::SystemTray;
using zclipboard::zGui::ZTable;
using zclipboard::zGui::ZWindow;

ZWindow::ZWindow(QWidget *zWindow) : QMainWindow(zWindow) {
    zIcon = QIcon(ICON_PATH);

    zCentralWidget = new QWidget(zWindow);
    zLayout = new QGridLayout(zCentralWidget);
    settings = new QSettings(AUTHOR_NAME, APP_NAME);

    setCentralWidget(zCentralWidget);
    setWindowTitle(APP_NAME);

    resize(AppConfig::Z_WINDOW_WIDTH, AppConfig::Z_WINDOW_HEIGHT);
    setWindowIcon(zIcon);

    setupGui();
    translatorDectect();
}

void ZWindow::setupGui() {
    ztable = new ZTable();
    zSearchArea = new SearchArea();
    clearButton = new ClearButton();
    getButton = new GetButton();
    settingButton = new SettingButton();
    disconnectButton = new DisconnectButton();
    systemTray = new SystemTray();

    ztable->addZtable(this, zLayout);
    zSearchArea->addSearchPanel({.zWindow = this, .zLayout = zLayout, .table = ztable});
    clearButton->addClearButton(zLayout, ztable);
    getButton->addGetButton(this, zLayout);
    settingButton->addSettingButton(this, zLayout);
    disconnectButton->addDisconnectButton(
        {.parent = this, .layout = zLayout, .getButton = getButton});
    systemTray->addSystemTray({.window = this, .icon = zIcon});

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

void ZWindow::translatorDectect() {
    if (!zUtils::getLanguageSetting()) {
        settings->setValue(LANGUAGE_SETTING, Translate::ENGLISH);
        return;
    }

    switch (settings->value(LANGUAGE_SETTING).toInt()) {
        case Translate::ENGLISH:
            break;

        case Translate::VIETNAMESE:
            loadVietNameseTranslator();
            break;
    }
}

void ZWindow::loadVietNameseTranslator() {
    clearButton->getClearButton()->setText(CLEAR_HISTORY_VI);
    getButton->getConnectButton()->setText(GET_CONTENT_BUTTON_VI);
    settingButton->getSettingButton()->setText(SETTING_BUTTON_VI);
    disconnectButton->getDisconnectButton()->setText(DISCONNECT_VI);
    zSearchArea->getSearchPanel()->setPlaceholderText(SEARCH_PANEL_VI);
}