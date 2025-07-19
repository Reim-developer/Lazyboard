#include "Include/CoreSystemTray.hpp"
#include "../Language/Include/Language.hpp"
#include "../Language/Include/Translate.hpp"
#include "../GUI/Include/Window.hpp"
#include "../GUI/Include/LanguageManager.hpp"
#include "../Utils/Include/Utils.hpp"
#include "../Utils/Include/Settings.hpp"

using ZClipboard::Core::SystemTrayCore;
using ZClipboard::Core::SystemTrayParams;
using ZClipboard::Language::Translate;
using ZClipboard::GUI::LanguageManager;
using ZClipboard::GUI::AppMainWindow;
using ZClipboard::AppUtils::Utils;

#if defined (Z_DEBUG)
    #include "../Utils/Include/AssertNullPtr.hpp"
    #include "../Utils/Include/Logging.hpp"
    
    using ZClipboard::AppUtils::LogContext;
#endif

void SystemTrayCore::UpdateSwitchLanguage(const SystemTrayParams &params) {
    auto menu = params.trayMenu;
    auto window = params.window;
    
    #if defined (Z_DEBUG)
        AssertContext{}.RequireNonNullPtr(menu);
        AssertContext{}.RequireNonNullPtr(params.settings);
        AssertContext{}.RequireNonNullPtr(window);

        LogContext{}.LogDebug(&menu);
        LogContext{}.LogDebug(&window);
        LogContext{}.LogDebug(&params.settings);
    #endif

    connect(&LanguageManager::GetLanguageManager(), 
            &LanguageManager::OnLanguageChanged, this, 
              [this, menu, window](int newLanguage) {

        struct SystemTrayParams params {
            .window = window,
            .trayMenu = menu,
            .TYPE = newLanguage
        };

        LoadTranslator(params); 
    });

}

void SystemTrayCore::SetupTranslator(const SystemTrayParams &params) {
    if (!Utils::hasSetting(LANGUAGE_SETTING)) {
        params.settings->setValue(LANGUAGE_SETTING, Translate::ENGLISH);
    }

    const int TYPE = params.settings->value(LANGUAGE_SETTING).toInt();

    struct SystemTrayParams systemTrayParams {
        .window = params.window,
        .trayMenu = params.trayMenu,
        .TYPE = TYPE
    };

    LoadTranslator(systemTrayParams);
}

void SystemTrayCore::LoadTranslator(const SystemTrayParams &params) {
    params.trayMenu->clear();

    switch (params.TYPE) {
        case Translate::ENGLISH: {
            auto showAction = params.trayMenu->addAction(TRAY_SHOW_OPTION_EN);
            auto hideAction = params.trayMenu->addAction(TRAY_HIDE_OPTION_EN);
            auto quitAction = params.trayMenu->addAction(TRAY_QUIT_OPTION_EN);

            connect(showAction, &QAction::triggered, params.window, &AppMainWindow::showNormal);
            connect(quitAction, &QAction::triggered, params.window, &QApplication::quit);
            connect(hideAction, &QAction::triggered, params.window, &AppMainWindow::hide);
            break;
        }

        case Translate::VIETNAMESE: {
            auto showAction = params.trayMenu->addAction(TRAY_SHOW_OPTION_VI);
            auto hideAction = params.trayMenu->addAction(TRAY_HIDE_OPTION_VI);
            auto quitAction = params.trayMenu->addAction(TRAY_QUIT_OPTION_VI);

            connect(showAction, &QAction::triggered, params.window, &AppMainWindow::showNormal);
            connect(quitAction, &QAction::triggered, params.window, &QApplication::quit);
            connect(hideAction, &QAction::triggered, params.window, &AppMainWindow::hide);
            break;
        }
    }
}