#include "Include/DisconnectButton.hpp"
#include "../Listener/Include/ListenerDisconnect.hpp"
#include <QPushButton>
#include <QtGlobal>
#include "../Core/Include/CoreDisconnect.hpp"
#include "../Utils/Include/Config.hpp"
#include "Include/GetConnectButton.hpp"

#if defined (Z_DEBUG)
    #include "../Utils/Include/AssertNullPtr.hpp"
#endif

using ZClipboard::Listener::DisconnectImpl;
using ZClipboard::GUI::DisconnectButton;

using Self = DisconnectButton;
using Toolkit = ComponentsToolkit;
using Window = QMainWindow;
using Impl = DisconnectImpl;

Self *Self::UseConnectButton(ConnectButton *button) {
    this->getButton = button;

    return this;
}

void Self::SetupDisconnectButton(Toolkit *toolkit, Window *window) {
    Utils::MakeSmartPtr<QSettings>(settings, AUTHOR_NAME, APP_NAME);
    auto disconnectButton = toolkit->GetDisconnectButton();

    #if defined (Z_DEBUG)
        AssertContext{}.RequireNonNullPtr(disconnectButton);
        AssertContext{}.RequireNonNullPtr(settings.get());
        AssertContext{}.RequireNonNullPtr(toolkit);
        AssertContext{}.RequireNonNullPtr(window);
        AssertContext{}.RequireNonNullPtr(getButton);
    #endif

    const auto Function = BuilderFunc
        .   StartBuild()
        ->  WithAndThen(&Impl::setting, settings.get())
        ->  WithAndThen(&Impl::getButton, getButton)
        ->  WithAndThen(&Impl::toolkit, toolkit)
        ->  WithAndThen(&Impl::windowParent, window)
        ->  WhenDone()
        ->  TryGetListener();

    Builder
        .   StartBuild(disconnectButton)
        ->  WhenDone()
        ->  AddListener(Function);
}
