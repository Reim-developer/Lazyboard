#ifndef NETWORK_STATE_HPP
#include "../../Utils/Include/Namespace_Macro.hpp"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include "../../Lib_Memory/Include/Memory.hpp"

using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::Lib_Memory::MakePtr;

NETWORK_NAMESPACE

    class NetworkState {
        public:
            NetworkState();

        public:
            QTcpServer *GetServer();
            QTcpSocket *GetSocket();
            void ResetServer();
            void ResetSocket();

        private:
            PtrUnique<QTcpServer> server;
            PtrUnique<QTcpSocket> socket;
    };

END_NAMESPACE
#endif // NETWORK_STATE_HPP