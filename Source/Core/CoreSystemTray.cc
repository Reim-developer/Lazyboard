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

void SystemTrayCore::updateSwitchLanguageInstance(const SystemTrayParams &params) {
    QMenu *menu = params.trayMenu;
    QMainWindow *window = params.window;

    // clang-format off
    connect(&LanguageManager::instance(), 
            &LanguageManager::languageChanged, this, 
              [this, menu, window](int newLanguage) {

        struct SystemTrayParams params {
            .window = window,
            .trayMenu = menu,
            .TYPE = newLanguage
        };
        loadTranslator(params); 
    });

    // clang-format on
}

void SystemTrayCore::translatorDectect(const SystemTrayParams &params) {
    if (!Utils::hasSetting(LANGUAGE_SETTING)) {
        params.settings->setValue(LANGUAGE_SETTING, Translate::ENGLISH);
    }

    const int TYPE = params.settings->value(LANGUAGE_SETTING).toInt();

    // clang-format off
    struct SystemTrayParams systemTrayParams {
        .window = params.window,
        .trayMenu = params.trayMenu,
        .TYPE = TYPE
    };
    // clang-format on

    loadTranslator(systemTrayParams);
}

void SystemTrayCore::loadTranslator(const SystemTrayParams &params) {
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