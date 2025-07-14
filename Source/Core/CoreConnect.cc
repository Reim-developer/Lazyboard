#include "Include/CoreConnect.hpp"
#include <QObject>

using ZClipboard::Core::CoreConnect;

void CoreConnect::ThenAddListener(VOID_FUNC Function) {
    auto button = Impl.get()->button;

    QObject::connect(button, &QPushButton::clicked, Function);
}