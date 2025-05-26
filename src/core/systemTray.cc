#include "include/systemTray.hpp"
#include "../language/include/language.hpp"
#include "../language/include/translate.hpp"
#include "../zGui/include/zwindow.hpp"
#include "../zGui/include/LanguageManager.hpp"
#include "../zUtils/include/zUtils.hpp"
#include "../zUtils/include/settings.hpp"

using zclipboard::core::SystemTrayCore;
using zclipboard::core::SystemTrayParams;
using zclipboard::language::Translate;
using zclipboard::zGui::LanguageManager;
using zclipboard::zGui::ZWindow;

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
    if (!zUtils::getLanguageSetting()) {
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

            connect(showAction, &QAction::triggered, params.window, &ZWindow::showNormal);
            connect(quitAction, &QAction::triggered, params.window, &QApplication::quit);
            connect(hideAction, &QAction::triggered, params.window, &ZWindow::hide);
            break;
        }

        case Translate::VIETNAMESE: {
            auto showAction = params.trayMenu->addAction(TRAY_SHOW_OPTION_VI);
            auto hideAction = params.trayMenu->addAction(TRAY_HIDE_OPTION_VI);
            auto quitAction = params.trayMenu->addAction(TRAY_QUIT_OPTION_VI);

            connect(showAction, &QAction::triggered, params.window, &ZWindow::showNormal);
            connect(quitAction, &QAction::triggered, params.window, &QApplication::quit);
            connect(hideAction, &QAction::triggered, params.window, &ZWindow::hide);
            break;
        }
    }
}