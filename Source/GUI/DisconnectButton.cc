#include "Include/DisconnectButton.hpp"
#include "../Listener/Include/ListenerDisconnect.hpp"
#include <QPushButton>
#include <QtGlobal>
#include "../Core/Include/CoreDisconnect.hpp"
#include "../Utils/Include/Config.hpp"
#include "Include/GetConnectButton.hpp"

using ZClipboard::Listener::DisconnectImpl;
using ZClipboard::GUI::DisconnectButton;

#define __SELF__ DisconnectButton
#define __TOOKIT__ ComponentsToolkit
#define __WINDOW__ QMainWindow
#define __IMPL__ DisconnectImpl

__SELF__ *__SELF__::UseConnectButton(GetButton *button) {
    this->getButton = button;

    return this;
}

void __SELF__::SetupDisconnectButton(__TOOKIT__ *toolkit, __WINDOW__ *window) {
    Utils::MakeSmartPtr<QSettings>(settings, AUTHOR_NAME, APP_NAME);
    auto disconnectButton = toolkit->GetDisconnectButton();

    const auto Function = BuilderFunc
        .   StartBuild()
        ->  WithAndThen(&__IMPL__::setting, settings.get())
        ->  WithAndThen(&__IMPL__::getButton, getButton)
        ->  WithAndThen(&__IMPL__::toolkit, toolkit)
        ->  WithAndThen(&__IMPL__::windowParent, window)
        ->  WhenDone()
        ->  TryGetListener();


    Builder
        .   StartBuild(disconnectButton)
        ->  WhenDone()
        ->  AddListener(Function);
}
