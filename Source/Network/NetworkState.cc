#include "Include/NetworkState.hpp"
#include "../Utils/Include/Meta_Macro.hpp"
#include "qtcpsocket.h"

using ZClipboard::Network::NetworkState;

NetworkState::NetworkState() {
    #if !defined (_WIN32)

        MAKE_SMART_PTR(QTcpServer, server);
        MAKE_SMART_PTR(QTcpSocket, socket);

    #else

        server = MakePtr<QTcpServer>();
        socket = MakePtr<QTcpSocket>();

    #endif
}

QTcpServer *NetworkState::GetServer() {
    if(!server) {
        #if !defined(_WIN32)

            MAKE_SMART_PTR(QTcpServer, server);

        #else

            server = MakePtr<QTcpServer>();

        #endif
    }

    return server.get();
}

QTcpSocket *NetworkState::GetSocket() {
    if(!socket) {
          #if !defined(_WIN32)

            MAKE_SMART_PTR(QTcpSocket, socket);

        #else

            socket = MakePtr<QTcpSocket>();

        #endif
    }

    return socket.get();
}

void NetworkState::ResetServer() {
    if(server) {
        server->close();
        server->deleteLater();
        server = nullptr;
    }
}

void NetworkState::ResetSocket() {
    if(socket) {
        socket->deleteLater();
        socket = nullptr;
    }
}
