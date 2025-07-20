#ifndef LISTENER_DISCONNECT_HPP
#define LISTENER_DISCONNECT_HPP
#include <QSettings>
#include "../../Lib_Memory/Include/Memory.hpp"
#include "../../GUI/Include/GetConnectButton.hpp"
#include "ListenerClearCache.hpp"
#include "../../Utils/Include/Meta_Macro.hpp"
#include "../../GUI/Toolkit/Include/MainWindow_Components.hpp"
#include <QMainWindow>

using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::Lib_Memory::MakePtr;
using ZClipboard::GUI::ConnectButton;
using ZClipboard::GUI::Toolkit::MainWindowComponentsManager;

LISTENER_NAMESPACE

    struct DisconnectImpl {
        QSettings *setting;
        MainWindowComponentsManager *componentsManager;
        ConnectButton *getButton;
        QMainWindow *windowParent;
    };

    class ListenerDisconnect {
        private:
            PtrUnique<DisconnectImpl> Impl;

        public:
            ListenerDisconnect *StartBuild() {
                Impl = MakePtr<DisconnectImpl>();

                return this;
            }

            CLASS_BUILD(T, V)
            ListenerDisconnect *WithAndThen(T DisconnectImpl::*member, V &&value) {
                Impl.get()->*member = FORWARD(V, value);

                return this;
            }

            ListenerDisconnect *WhenDone() {
                return this;
            }

            VOID_FUNC TryGetListener();
    };

END_NAMESPACE

#endif // LISTENER_DISCONNECT_HPP