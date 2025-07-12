#include "GUI/Include/Window.hpp"
#include "Preload/Include/PreloadTheme.hpp"
#include "Preload/Include/PreloadPassword.hpp"
#include "Core/Include/Enum.hpp"
#include <QApplication>
#include <memory>

using std::make_unique;
using std::unique_ptr;
using ZClipboard::Core::LoginState;
using ZClipboard::Preload::Application;
using ZClipboard::Preload::PreloadPassword;
using ZClipboard::GUI::AppMainWindow;

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
        AppMainWindow window;
        window.show();

        return application.exec();
    }

    return static_cast<int>(LoginState::LOGIN_FAILED);
}