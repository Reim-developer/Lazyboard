#include "include/disconnectButton.hpp"
#include "../listener/include/ListenerDisconnect.hpp"
#include "../lib_memory/include/memory.hpp"
#include <QPushButton>
#include <QMessageBox>
#include <QStringLiteral>
#include "../core/include/CoreDisconnect.hpp"
#include "../zUtils/include/config.hpp"

using zclipboard::zGui::DisconnectButton;
using zclipboard::listener::DisconnectImpl;
using zclipboard::lib_memory::MakePtr;

void DisconnectButton::addDisconnectButton(QMainWindow *parent, GetButton *getButton, QGridLayout *layout) {
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