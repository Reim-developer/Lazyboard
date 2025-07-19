#include "Include/GetConnectButton.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Utils/Include/Utils.hpp"
#include <QSettings>

using ZClipboard::GUI::ConnectButton;
using ZClipboard::Core::CoreConnectImpl;
using ZClipboard::Listener::ListenerConnectImpl;
using ZClipboard::AppUtils::Utils;

using Self = ConnectButton;
using Window = QMainWindow;
using Button = QPushButton;

void Self::SetupConnectButton(Window *window, Toolkit *toolkit) {
    Utils::MakeSmartPtr<QSettings>(settings, AUTHOR_NAME, APP_NAME);
    Utils::MakeSmartPtr<NetworkState>(networkState);

    auto connectButton = toolkit->GetConnectButton();
    this->SetupEventListener(window, connectButton);
}

void Self::SetupEventListener(Window *window, Button *button) {
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

void Self::ResetServer() {
    networkState->ResetServer();
    networkState->ResetSocket();
}

NetworkState *Self::GetNetworkState() {
    return networkState.get();
}