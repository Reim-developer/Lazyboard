#include "Include/DisconnectButton.hpp"
#include "../Listener/Include/ListenerDisconnect.hpp"
#include <QPushButton>
#include <QtGlobal>
#include "../Core/Include/CoreDisconnect.hpp"
#include "../Utils/Include/Config.hpp"

using ZClipboard::Listener::DisconnectImpl;
using ZClipboard::GUI::DisconnectButton;

void DisconnectButton::addDisconnectButton(QMainWindow *parent, GetButton *getButton, QGridLayout *layout) {
    /*
    * That macro only work in Linux/Darwin.
    */
    #if !defined (_WIN32)
        MAKE_SMART_PTR(QPushButton, disconnectButton);
        MAKE_SMART_PTR(QSettings, settings, (AUTHOR_NAME, APP_NAME));
        ADD_LAYOUT_TO(layout, disconnectButton.get(), 0, 4);
    #endif

    disconnectButton = MakePtr<QPushButton>();
    settings = MakePtr<QSettings>(AUTHOR_NAME, APP_NAME);
    layout->addWidget(disconnectButton.get(), 0, 4);
     

    const auto Function = BuilderFunc
        .   StartBuild()
        ->  WithAndThen(&DisconnectImpl::windowParent, parent)
        ->  WithAndThen(&DisconnectImpl::setting, settings.get())
        ->  WithAndThen(&DisconnectImpl::getButton, getButton)
        ->  WhenDone()
        ->  TryGetListener();


    Builder
        .   StartBuild(disconnectButton.get())
        ->  WhenDone()
        ->  AddListener(Function);
}

QPushButton *DisconnectButton::getDisconnectButton() {
    return disconnectButton.get();
}