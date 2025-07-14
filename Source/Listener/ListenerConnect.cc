#include "Include/ListenerConnect.hpp"
#include "../Language/Include/Language.hpp"
#include "../Utils/Include/Settings.hpp"
#include <QMessageBox>
#include <QObject>
#include <QTcpSocket>
#include <QApplication>
#include <QClipboard>
#include <QString>

using ZClipboard::Listener::ListenerConnect;

QSettings *ListenerConnect::GetSettings() {
    auto settings = this
        ->  Impl
        ->  settings;

        return settings;

    return settings;
}

QMainWindow *ListenerConnect::GetMainWindow() {
    auto window = this
            ->  Impl
            ->  window;

        return window;
    
    return window;
}

QTcpServer *ListenerConnect::GetServer() {
    auto server = this
            ->  Impl
            ->  networkState
            ->  GetServer();

    return server;
}

QTcpSocket *ListenerConnect::GetSocket() {
    auto socket = this
            ->  Impl
            ->  networkState
            -> GetSocket();

        return socket;
   
    return socket;
}

bool ListenerConnect::IsServerAlreadyRun() {
    auto server = this->GetServer();

    if (server && server->isListening()) {

        auto settings = this->GetSettings();
        auto window = this->GetMainWindow();

        const auto LANG_TYPE = settings->value(LANGUAGE_SETTING).toInt();
        auto const DIALOG_TITLE = LANG_TYPE ? DIALOG_INFO_TITLE_VI : DIALOG_INFO_TITLE_EN;
        auto const DIALOG_MESSAGE = LANG_TYPE ? SERVER_ALREADY_ERR_VI : SERVER_ALREADY_ERR_EN;

        QMessageBox::information(window, DIALOG_TITLE, DIALOG_MESSAGE);

        return true;
    }

    return false;
}

bool ListenerConnect::IsRunningError() {
    auto server = this->GetServer();
    auto settings = this->GetSettings();
    auto window = this->GetMainWindow();


    if (!server->listen(QHostAddress::AnyIPv4, 8000)) {

        const auto LANG_TYPE =  settings->value(LANGUAGE_SETTING).toInt();
        auto const DIALOG_TITLE = LANG_TYPE ? DIALOG_ERROR_TITLE_VI : DIALOG_ERROR_TITLE_EN;
        auto const DIALOG_MESSAGE = LANG_TYPE ? COULD_NOT_START_SERVER_ERR_VI : COULD_NOT_START_SERVER_ERR_EN;

        QMessageBox::critical(window, DIALOG_TITLE, DIALOG_MESSAGE + server->errorString());
        server->deleteLater();
        server = nullptr;

        return true;
    }

    return false;
}

void ListenerConnect::Connect() {
    const auto NewConnectFn = [this]() {
        auto server = this->GetServer();

        QObject::connect(server, &QTcpServer::newConnection, [this, server]() {
            auto socket = this->GetSocket();

            if(!socket) {
                qDebug() << "Socket is null ptr";
                return;
            }

            socket = server->nextPendingConnection();

            QObject::connect(socket, &QTcpSocket::readyRead, [this, socket]() {
                QApplication::clipboard()->setText(QString::fromUtf8(socket->readAll()));
            });
        });
    };


    NewConnectFn();
}


VOID_FUNC ListenerConnect::TryGetListener() {
    const auto Function = [this]() {
        const auto IsRunningFn = IsServerAlreadyRun();

        if(!IsRunningFn) {
            if(!IsRunningError()) {
                const auto LANG_TYPE = this
                    ->  GetSettings()
                    ->  value(LANGUAGE_SETTING)
                    .   toInt();
                    
                const auto TYPE_TRANS = LANG_TYPE ? GET_CONTENT_WAIT_BUTTON_VI : GET_CONTENT_WAIT_BUTTON_EN;

                this
                    ->  Impl
                    ->  button
                    ->  setText(TYPE_TRANS);

                this->Connect();
                
                #if !defined (_WIN32)

                    MAKE_SMART_PTR(PeerDiscovery, this->peerDiscovery,(45454, 
                this
                        ->  Impl
                        ->  window
                    ));

                #else 

                    this->peerDiscovery = MakePtr<PeerDiscovery>(
                        45454,
                        this
                            ->  Impl
                            ->  window
                    );

                #endif
            }
        }

    };

    return Function;
}