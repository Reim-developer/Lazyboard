#include "include/systemTray.hpp"
#include "../language/include/language.hpp"
#include "../language/include/translate.hpp"
#include "../zGui/include/zwindow.hpp"
#include "../zGui/include/LanguageManager.hpp"

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
            .trayMenu = menu,
            .window = window,
            .TYPE = newLanguage
        };
        loadTranslator(params); 
    });

    // clang-format on
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
            connect(showAction, &QAction::triggered, params.window, &ZWindow::hide);
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