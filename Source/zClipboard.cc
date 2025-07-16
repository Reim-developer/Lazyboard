#include "GUI/Include/Window.hpp"
#include "Imlements/Include/Theme_Impl.hpp"
#include "Preload/Include/PreloadPassword.hpp"
#include "Core/Include/Enum.hpp"
#include <QApplication>

using ZClipboard::Core::LoginState;
using ZClipboard::Preload::PreloadPassword;
using ZClipboard::Implements::Theme_Impl;
using ZClipboard::GUI::AppMainWindow;

int main(int argc, char *argv[]) {
    PtrUnique<QApplication> application = MakePtr<QApplication>(argc, argv);
    PtrUnique<Theme_Impl> zClipboard_Impl = MakePtr<Theme_Impl>();
    PtrUnique<PreloadPassword> preloadPassword = MakePtr<PreloadPassword>();

    const auto LOGIN_STATUS = preloadPassword->showLoginForm();

    if (LoginState::LOGIN_OK == LOGIN_STATUS || LoginState::LOGIN_NOT_SET == LOGIN_STATUS) {
        AppMainWindow window;
        
        zClipboard_Impl
            ->  StartBuild()
            ->  ThemeImplement(application.get());
        window.show();
        return application->exec();
    }

    return static_cast<int>(LoginState::LOGIN_FAILED);
}
