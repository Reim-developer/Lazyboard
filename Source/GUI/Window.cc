#include "Include/Window.hpp"
#include "Include/LanguageManager.hpp"
#include "Include/ClearButton.hpp"
#include "Include/GetConnectButton.hpp"
#include "Include/SettingDialog.hpp"
#include "Include/TableView.hpp"
#include "Include/SearchPanel.hpp"
#include "../Utils/Include/Utils.hpp"
#include "../Utils/Include/Settings.hpp"
#include "../Language/Include/Translate.hpp"
#include "Include/DisconnectButton.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Language/Include/Language.hpp"
#include "Include/SystemTray.hpp"
#include <QStringLiteral>
#include <QApplication>
#include "../Lib_Memory/Include/Memory.hpp"
#include <QSettings>

using ZClipboard::Language::Translate;
using ZClipboard::Language::TransValue;
using ZClipboard::GUI::DisconnectButton;
using ZClipboard::GUI::GetButton;
using ZClipboard::GUI::SearchArea;
using ZClipboard::GUI::SearchPanelWidget;
using ZClipboard::GUI::SystemTray;
using ZClipboard::GUI::SystemTrayWidget;
using ZClipboard::GUI::TableView;
using ZClipboard::GUI::AppMainWindow;
using ZClipboard::Lib_Memory::MakePtr;
using ZClipboard::AppUtils::Utils;

AppMainWindow::AppMainWindow(QWidget *zWindow) : QMainWindow(zWindow) {
    appIcon = QIcon(ICON_PATH);

    centralWidget = new QWidget(zWindow);
    windowLayout = new QGridLayout(centralWidget);
    settings = new QSettings(AUTHOR_NAME, APP_NAME);

    setCentralWidget(centralWidget);
    setWindowTitle(APP_NAME);

    resize(AppConfig::Z_WINDOW_WIDTH, AppConfig::Z_WINDOW_HEIGHT);
    setWindowIcon(appIcon);

    SetupApplicationGUI();
    translatorDectect();

    Utils::MakeSmartPtr<HotReloadLanguage>(hotReloadLanguage);
    Utils::LogDebug("HotReloadLanguage instance address:", &hotReloadLanguage);

    hotReloadLanguage
        ->  StartBuild()
        ->  WithAndThen(&HotReloadImpl::windowContext, this)
        ->  WhenDone()
        ->  ThenAddListener([this] {
            this->Translator();            
    });
}

void AppMainWindow::SetupApplicationGUI() {
    tableView = MakePtr<TableView>();
    searchArea = new SearchArea();
    clearButton = new ClearButton();
    getButton = new GetButton();
    settingButton = new SettingButton();
    disconnectButton = new DisconnectButton();
    systemTray = new SystemTray(this);
    notificationCore = new NotificationCore();

    // clang-format off
    struct SearchPanelWidget searchPanelWidget {
        .window = this,
        .layout = windowLayout,
        .tableView = tableView.get()
    };


    struct SystemTrayWidget systemTrayWidget {
        .window = this,
        .icon = appIcon
    };
    
    tableView->SetupTableView(this, windowLayout);
    searchArea->SetupSearchPanel(searchPanelWidget);
    clearButton->SetupClearButton(windowLayout, tableView.get());
    getButton->SetupConnectButton(this, windowLayout);
    settingButton->addSettingButton(this, windowLayout);
    disconnectButton->addDisconnectButton(this, getButton, windowLayout);
    systemTray->addSystemTray(systemTrayWidget);

    const auto trayIcon = systemTray->getSystemTrayIcon();
    const auto clipboard = tableView->GetClipboard();

    notificationCore->onClipboardChanged(trayIcon, clipboard);

    connect(trayIcon, &QSystemTrayIcon::activated, this, &AppMainWindow::onTrayIconActivated);
}

void AppMainWindow::closeEvent(QCloseEvent *event) {
    if (Utils::hasSetting(AUTO_HIDE_SETTING)) {
        hide();
        event->ignore();
    } else {
        event->accept();
    }
}

void AppMainWindow::translatorDectect() {
    if (!Utils::hasSetting(LANGUAGE_SETTING)) {
        settings->setValue(LANGUAGE_SETTING, Translate::ENGLISH);
    }

    switch (settings->value(LANGUAGE_SETTING).toInt()) {
        case Translate::ENGLISH:
            Translator();
            break;

        case Translate::VIETNAMESE:
            Translator();
            break;
    }
}

void AppMainWindow::Translator() {
    const int TRANS_VALUE = settings->value(LANGUAGE_SETTING).toInt();
    const auto TRANS_TYPE = Utils::languageTypeCast(TRANS_VALUE);

    auto clearButtonWidget = clearButton->getClearButton();
    auto getButtonWidget = getButton->GetConnectButton();
    auto settingButtonWidget = settingButton->getSettingButton();
    auto discButtonWidget = disconnectButton->getDisconnectButton();
    auto searchPanel = searchArea->GetSearchPanel();

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

void AppMainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick) {
        showNormal();
        raise();
        activateWindow();
    }
}