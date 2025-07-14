#ifndef LISTENER_CONNECT_HPP
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../../Utils/Include/Meta_Macro.hpp"
#include "../../Utils/Include/Alias_Template.hpp"
#include "../../Lib_Memory/Include/Memory.hpp"
#include "../../Network/Include/NetworkDiscovery.hpp"
#include "../../Network/Include/NetworkState.hpp"
#include <QSettings>
#include <QtNetwork/QTcpServer>
#include <QMainWindow>
#include <QTcpSocket>
#include <QPushButton>

using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::Lib_Memory::MakePtr;
using ZClipboard::AppUtils::Func;
using ZClipboard::Network::PeerDiscovery;
using ZClipboard::Network::NetworkState;

LISTENER_NAMESPACE
    struct ListenerConnectImpl {
        QSettings *settings;
        QMainWindow *window;
        QPushButton *button;
        NetworkState *networkState;
    };

    class ListenerConnect {
        private:
            PtrUnique<ListenerConnectImpl> Impl;
            PtrUnique<PeerDiscovery> peerDiscovery;

        private:
            using ListenerImpl = ListenerConnectImpl;

        private:
            QSettings *GetSettings();
            QTcpServer *GetServer();
            QMainWindow *GetMainWindow();
            QTcpSocket  *GetSocket();
            bool IsServerAlreadyRun();
            bool IsRunningError();
            void Connect();

        public:
            ListenerConnect *StartBuild() {
                #if !defined (_WIN32)

                    MAKE_SMART_PTR(ListenerConnectImpl, Impl);

                #else

                    Impl = MakePtr<ListenerConnectImpl>();

                #endif 


                return this;
            }

            CLASS_BUILD(T, V)
            ListenerConnect *WithAndThen(T ListenerImpl::*member, V &&value) {
                Impl.get()->*member = FORWARD(V, value);

                return this;
            }

            ListenerConnect *WhenDone() {
                return this;
            }

            VOID_FUNC TryGetListener();
    };

END_NAMESPACE
#endif // LISTENER_CONNECT_HPP