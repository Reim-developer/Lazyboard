#ifndef DISCONNECT_BUTTON_HPP
#define DISCONNECT_BUTTON_HPP
#include <QPushButton>
#include <QGridLayout>
#include <QMainWindow>
#include "../../Lib_Memory/Include/Memory.hpp"
#include "GetConnectButton.hpp"
#include "../../Core/Include/CoreDisconnect.hpp"
#include "../../Listener/Include/ListenerDisconnect.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"

using ZClipboard::GUI::GetButton;
using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::Core::CoreDisconnect;
using ZClipboard::Listener::ListenerDisconnect;

GUI_NAMESPACE

    class DisconnectButton {
        private:
            PtrUnique<QSettings> settings;
            CoreDisconnect Builder;
            ListenerDisconnect BuilderFunc;
            PtrUnique<QPushButton> disconnectButton;

        public:
            void addDisconnectButton(QMainWindow *parent, GetButton *getButton, QGridLayout *layout);
            QPushButton *getDisconnectButton();
        };

END_NAMESPACE

#endif  // DISCONNECT_BUTTON_HPP