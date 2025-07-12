#include "Include/CoreDisconnect.hpp"
#include "../Lib_Memory/Include/Memory.hpp"
#include <QObject>

using ZClipboard::Core::CoreDisconnectImpl;
using ZClipboard::Core::CoreDisconnect;
using ZClipboard::Lib_Memory::MakePtr;

CoreDisconnect *CoreDisconnect::StartBuild(QPushButton *button) {
    Impl = MakePtr<CoreDisconnectImpl>();

    this
        ->  Impl
        ->  disconnectButton
        =   button;

    return this;
}

CoreDisconnect *CoreDisconnect::WhenDone() {
    return this;
}

void CoreDisconnect::AddListener(VOID_FUNC func) {
    auto button = Impl.get()->disconnectButton;

    QObject::connect(button, &QPushButton::clicked, func);
}