#include "include/zwindow.hpp"
#include "include/LanguageManager.hpp"
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
#include "../lib_memory/include/memory.hpp"
#include <QSettings>

using zclipboard::language::Translate;
using zclipboard::language::TransValue;
using zclipboard::zGui::DisconnectButton;
using zclipboard::zGui::DisconnectButtonWidget;
using zclipboard::zGui::GetButton;
using zclipboard::zGui::SearchArea;
using zclipboard::zGui::SearchPanelWidget;
using zclipboard::zGui::SystemTray;
using zclipboard::zGui::SystemTrayWidget;
using zclipboard::zGui::ZTable;
using zclipboard::zGui::ZWindow;
using zclipboard::lib_memory::MakePtr;

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

    connect(&LanguageManager::instance(), &LanguageManager::languageChanged, this,
            &ZWindow::loadTranslator);
}

void ZWindow::setupGui() {
    ztable = MakePtr<ZTable>();
    zSearchArea = new SearchArea();
    clearButton = new ClearButton();
    getButton = new GetButton();
    settingButton = new SettingButton();
    disconnectButton = new DisconnectButton();
    systemTray = new SystemTray(this);
    notificationCore = new NotificationCore();

    // clang-format off
    struct SearchPanelWidget searchPanelWidget {
        .zWindow = this,
        .zLayout = zLayout,
        .table = ztable.get()
    };

    struct DisconnectButtonWidget discButtonWidget {
        .parent = this,
        .layout = zLayout,
        .getButton = getButton
    };

    struct SystemTrayWidget systemTrayWidget {
        .window = this,
        .icon = zIcon
    };
    
    ztable->addZtable(this, zLayout);
    zSearchArea->addSearchPanel(searchPanelWidget);
    clearButton->addClearButton(zLayout, ztable.get());
    getButton->addGetButton(this, zLayout);
    settingButton->addSettingButton(this, zLayout);
    disconnectButton->addDisconnectButton(discButtonWidget);
    systemTray->addSystemTray(systemTrayWidget);

    const auto trayIcon = systemTray->getSystemTrayIcon();
    const auto clipboard = ztable->getClipboard();

    notificationCore->onClipboardChanged(trayIcon, clipboard);

    connect(trayIcon, &QSystemTrayIcon::activated, this, &ZWindow::onTrayIconActivated);
}

void ZWindow::closeEvent(QCloseEvent *event) {
    if (zUtils::hasSetting(AUTO_HIDE_SETTING)) {
        hide();
        event->ignore();
    } else {
        event->accept();
    }
}

void ZWindow::translatorDectect() {
    if (!zUtils::hasSetting(LANGUAGE_SETTING)) {
        settings->setValue(LANGUAGE_SETTING, Translate::ENGLISH);
    }

    switch (settings->value(LANGUAGE_SETTING).toInt()) {
        case Translate::ENGLISH:
            loadTranslator();
            break;

        case Translate::VIETNAMESE:
            loadTranslator();
            break;
    }
}

void ZWindow::loadTranslator() {
    const int TRANS_VALUE = settings->value(LANGUAGE_SETTING).toInt();
    const auto TRANS_TYPE = zUtils::languageTypeCast(TRANS_VALUE);

    auto clearButtonWidget = clearButton->getClearButton();
    auto getButtonWidget = getButton->getConnectButton();
    auto settingButtonWidget = settingButton->getSettingButton();
    auto discButtonWidget = disconnectButton->getDisconnectButton();
    auto searchPanel = zSearchArea->getSearchPanel();

    // clang-format off
    TransValue clearButtonTrans {
        .LANGUAGE_EN = CLEAR_HISTORY_EN, 
        .LANGUAGE_VI = CLEAR_HISTORY_VI
    };
    
    TransValue getButtonTrans {
        .LANGUAGE_EN = GET_CONTENT_BUTTON_EN,
        .LANGUAGE_VI = GET_CONTENT_BUTTON_VI
    };

    TransValue settingButtonTrans {
        .LANGUAGE_EN = SETTING_BUTTON_EN,
        .LANGUAGE_VI = SETTING_BUTTON_VI
    };

    TransValue discButtonTrans {
        .LANGUAGE_EN = DISCONNECT_EN, 
        .LANGUAGE_VI = DISCONNECT_VI
    };

    TransValue searchPanelTrans {
        .LANGUAGE_EN = SEARCH_PANEL_EN, 
        .LANGUAGE_VI = SEARCH_PANEL_VI
    };

    // clang-format on

    Translate::translatorWidget(clearButtonWidget, TRANS_TYPE, clearButtonTrans);
    Translate::translatorWidget(getButtonWidget, TRANS_TYPE, getButtonTrans);
    Translate::translatorWidget(settingButtonWidget, TRANS_TYPE, settingButtonTrans);
    Translate::translatorWidget(discButtonWidget, TRANS_TYPE, discButtonTrans);
    Translate::translatorWidget(searchPanel, TRANS_TYPE, searchPanelTrans);
}

void ZWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick) {
        showNormal();
        raise();
        activateWindow();
    }
}