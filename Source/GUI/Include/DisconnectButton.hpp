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
#include "../Toolkit/Include/MainWindow_Components.hpp"

using ZClipboard::GUI::ConnectButton;
using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::Core::CoreDisconnect;
using ZClipboard::Listener::ListenerDisconnect;
using ZClipboard::GUI::Toolkit::ComponentsToolkit;

GUI_NAMESPACE

    class DisconnectButton {
        private:
            PtrUnique<QSettings> settings;
            CoreDisconnect Builder;
            ListenerDisconnect BuilderFunc;
            ConnectButton *getButton;

        private:
            using Toolkit = ComponentsToolkit;
            using Self = DisconnectButton;

        public:
            Self *UseConnectButton(ConnectButton *button);
            void SetupDisconnectButton(Toolkit *toolkit, QMainWindow *window);
        };

END_NAMESPACE

#endif  // DISCONNECT_BUTTON_HPP