#include "Include/Window.hpp"
#include "Include/LanguageManager.hpp"
#include "../Utils/Include/Utils.hpp"
#include "../Utils/Include/Settings.hpp"
#include "../Language/Include/Translate.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Language/Include/Language.hpp"
#include "Include/SystemTray.hpp"
#include <QApplication>
#include "Toolkit/Include/MainWindow_Components.hpp"
#include "../Helper_Implements/Include/LayoutManager_Impl_Helper.hpp"

using ZClipboard::Language::Translate;
using ZClipboard::Language::TransValue;
using ZClipboard::Implements::MainWindowComponentsManagerData;
using ZClipboard::GUI::AppMainWindow;
using ZClipboard::AppUtils::Utils;

#define __TOOLKIT__ componentsManager
#define __TOOLKIT_RAW__ componentsManager.get()

AppMainWindow::AppMainWindow(QWidget *zWindow) : QMainWindow(zWindow) {
    appIcon = QIcon(ICON_PATH);

    centralWidget = new QWidget(zWindow);
    windowLayout = new QGridLayout(centralWidget);
    settings = new QSettings(AUTHOR_NAME, APP_NAME);

    setCentralWidget(centralWidget);
    setWindowTitle(APP_NAME);

    resize(AppConfig::WINDOW_WIDTH, AppConfig::WINDOW_HEIGHT);
    setWindowIcon(appIcon);

    InitiationObject();
    SetupApplicationGUI();
    translatorDectect();

    Utils::MakeSmartPtr<HotReloadLanguage>(hotReloadLanguage);
    hotReloadLanguage
        ->  StartBuild()
        ->  WithAndThen(&HotReloadImpl::windowContext, this)
        ->  WhenDone()
        ->  ThenAddListener([this] {
            this->Translator();            
    });

    SetupAppLayout(__TOOLKIT_RAW__, windowLayout);
    #if defined (Z_DEBUG)
        __LOG__
    #endif
}

void AppMainWindow::InitiationObject() {
    using Object = MainWindowObjectManager;
    using ComponentsManager = MainWindowComponentsManager;
    
    Utils::MakeSmartPtr<ComponentsManager>(__TOOLKIT__);
    Utils::MakeSmartPtr<Object>(objectManager);
    Utils::MakeSmartPtr<GUI_Manager>(manager_GUI);
    
    objectManager->InitiationObjects();
}

void AppMainWindow::SetupApplicationGUI() {
    using DataImpl = MainWindowComponentsManagerData;
    
    manager_GUI
        ->  StartBuild()
        ->  WithAndThen(&DataImpl::appIcon, &appIcon)
        ->  WithAndThen(&DataImpl::object, objectManager.get())
        ->  WithAndThen(&DataImpl::toolkit, __TOOLKIT_RAW__)
        ->  WithAndThen(&DataImpl::window, this)
        ->  WhenDone()
        ->  Render_MainWindow_GUI();

    const auto trayIcon = __TOOLKIT__->GetSystemTrayIcon();
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

    auto clearButtonWidget = __TOOLKIT__->GetClearButton();
    auto getButtonWidget = __TOOLKIT__->GetConnectButton();
    auto settingButtonWidget = __TOOLKIT__->GetSettingButton();
    auto disconnectButtonWidget = __TOOLKIT__->GetDisconnectButton();
    auto searchPanel = __TOOLKIT__->GetSearchArea();

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
    Translate::translatorWidget(disconnectButtonWidget, TRANS_TYPE, discButtonTrans);
    Translate::translatorWidget(searchPanel, TRANS_TYPE, searchPanelTrans);
}

void AppMainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick) {
        showNormal();
        raise();
        activateWindow();
    }
}