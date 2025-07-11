#include "include/CoreDisconnect.hpp"
#include "../lib_memory/include/memory.hpp"
#include <QObject>

using zclipboard::core::CoreDisconnectImpl;
using zclipboard::core::CoreDisconnect;
using zclipboard::lib_memory::MakePtr;

CoreDisconnect *CoreDisconnect::StartBuild(QPushButton *button) {
    coreDisconnectImpl = MakePtr<CoreDisconnectImpl>();

    this
        ->  coreDisconnectImpl
        ->  disconnectButton
        =   button;

    return this;
}

CoreDisconnect *CoreDisconnect::WhenDone() {
    return this;
}

void CoreDisconnect::AddListener(VOID_FUNC func) {
    auto button = coreDisconnectImpl.get()->disconnectButton;

    QObject::connect(button, &QPushButton::clicked, func);
}