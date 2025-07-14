#include "Include/GetConnectButton.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Utils/Include/Meta_Macro.hpp"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>
#include <QSettings>

using ZClipboard::Language::TransValue;
using ZClipboard::GUI::GetButton;
using ZClipboard::Core::CoreConnectImpl;
using ZClipboard::Lib_Memory::MakePtr;
using ZClipboard::Listener::ListenerConnectImpl;

void GetButton::SetupConnectButton(QMainWindow *window, QGridLayout *layout) {
    #if !defined (_WIN32)

        MAKE_SMART_PTR(QPushButton, getButton);
        MAKE_SMART_PTR(QSettings, settings, (AUTHOR_NAME, APP_NAME));
        MAKE_SMART_PTR(NetworkState, networkState);
        ADD_LAYOUT_TO(layout, getButton.get(), 0, 1);

    #else

        getButton = MakePtr<QPushButton>();
        settings = MakePtr<QSettings>(AUTHOR_NAME, APP_NAME);
        networkState = MakePtr<NetworkState>();
        layout->addWidget(getButton.get(), 0, 1);

    #endif 

    using FnImpl = ListenerConnectImpl;
    auto Function = BuilderFn
        .   StartBuild()
        ->  WithAndThen(&FnImpl::networkState, networkState.get())
        ->  WithAndThen(&FnImpl::window, window)
        ->  WithAndThen(&FnImpl::button, getButton.get())
        ->  WithAndThen(&FnImpl::settings, settings.get())
        ->  WhenDone()
        ->  TryGetListener();


    using CoreImpl = CoreConnectImpl;
    BuilderCore
        .   StartBuild()
        ->  WithAndThen(&CoreImpl::button, getButton.get())
        ->  WhenDone()
        ->  ThenAddListener(Function);
}

void GetButton::ResetServer() {
    networkState->ResetServer();
    networkState->ResetSocket();
}

QPushButton *GetButton::GetConnectButton() {
    return getButton.get();
}

NetworkState *GetButton::GetNetworkState() {
    return networkState.get();
}