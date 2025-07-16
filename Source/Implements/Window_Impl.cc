#include "Include/Window_Impl.hpp"

using ZClipboard::Implements::WindowImplement;

#define __SELF__ WindowImplement

bool __SELF__::PreloadPasswordCheck() {
    if(!preloadPassword) {
        Utils::MakeSmartPtr<PreloadPassword>(preloadPassword);
    }

    const auto LOGIN_STATUS = preloadPassword->showLoginForm();

    if(LOGIN_STATUS == LoginState::LOGIN_NOT_SET || LOGIN_STATUS == LoginState::LOGIN_OK) {
        return true;
    }

    return false;
}

int __SELF__::LaunchWindow(QApplication *application) {
    if(!window) {
        Utils::MakeSmartPtr<Window>(window);
    }

    if(!themeImpl) {
        Utils::MakeSmartPtr<Theme_Impl>(themeImpl);
    }

    if(PreloadPasswordCheck()) {
        themeImpl
            ->  StartBuild()
            ->  ThemeImplement(application);

        window->show();

        __LOG__
        return application->exec();
    }
    __LOG__

    return static_cast<int>(LoginState::LOGIN_FAILED);
}