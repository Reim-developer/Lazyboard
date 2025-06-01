#include "zGui/include/zwindow.hpp"
#include "preload/include/theme.hpp"
#include "preload/include/password.hpp"
#include "core/include/enum.hpp"
#include <QApplication>
#include <memory>

using std::make_unique;
using std::unique_ptr;
using zclipboard::core::LoginState;
using zclipboard::preload::Application;
using zclipboard::preload::PreloadPassword;
using zclipboard::zGui::ZWindow;

int main(int argc, char *argv[]) {
    unique_ptr<Application> preloadApplication = make_unique<Application>();
    unique_ptr<PreloadPassword> preloadPassword = make_unique<PreloadPassword>();

    const bool IS_DEFAULT_THEME = preloadApplication->loadDefaultTheme();

    QApplication application(argc, argv);
    if (!IS_DEFAULT_THEME) {
        preloadApplication->loadSettingTheme(application);
    }

    preloadApplication->onSettingThemeChanged(application);
    const auto LOGIN_STATUS = preloadPassword->showLoginForm();

    qDebug() << static_cast<int>(LOGIN_STATUS);
    if (LoginState::LOGIN_OK == LOGIN_STATUS || LoginState::LOGIN_NOT_SET == LOGIN_STATUS) {
        ZWindow zWindow;
        zWindow.show();

        return application.exec();
    }

    return static_cast<int>(LoginState::LOGIN_FAILED);
}