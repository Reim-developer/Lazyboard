#include "Include/GetConnectButton.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Utils/Include/Utils.hpp"
#include <QSettings>

using ZClipboard::GUI::GetButton;
using ZClipboard::Core::CoreConnectImpl;
using ZClipboard::Listener::ListenerConnectImpl;
using ZClipboard::AppUtils::Utils;

#define __SELF__ GetButton
#define __WINDOW__ QMainWindow
#define __BUTTON__ QPushButton

void __SELF__::SetupConnectButton(QMainWindow *window, Toolkit *toolkit) {
    Utils::MakeSmartPtr<QSettings>(settings, AUTHOR_NAME, APP_NAME);
    Utils::MakeSmartPtr<NetworkState>(networkState);

    auto connectButton = toolkit->GetConnectButton();
    this->SetupEventListener(window, connectButton);
}

void __SELF__::SetupEventListener(__WINDOW__ *window, __BUTTON__ *button) {
    using FnImpl = ListenerConnectImpl;
    auto Function = BuilderFn
        .   StartBuild()
        ->  WithAndThen(&FnImpl::networkState, networkState.get())
        ->  WithAndThen(&FnImpl::window, window)
        ->  WithAndThen(&FnImpl::button, button)
        ->  WithAndThen(&FnImpl::settings, settings.get())
        ->  WhenDone()
        ->  TryGetListener();


    using CoreImpl = CoreConnectImpl;
    BuilderCore
        .   StartBuild()
        ->  WithAndThen(&CoreImpl::button, button)
        ->  WhenDone()
        ->  ThenAddListener(Function);
}

void GetButton::ResetServer() {
    networkState->ResetServer();
    networkState->ResetSocket();
}

NetworkState *GetButton::GetNetworkState() {
    return networkState.get();
}