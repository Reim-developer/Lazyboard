#include "include/getButton.hpp"
#include "../zUtils/include/settings.hpp"
#include "../language/include/language.hpp"
#include "../zUtils/include/config.hpp"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>
#include <QSettings>

using zclipboard::language::TransValue;
using zclipboard::zGui::GetButton;

void GetButton::addGetButton(QWidget *window, QGridLayout *layout) {
    getButton = new QPushButton(window);
    settings = new QSettings(AUTHOR_NAME, APP_NAME);

    type = settings->value(LANGUAGE_SETTING).toInt();
    connect(getButton, &QPushButton::clicked, this, [this, window]() {
        const auto TYPE_TRANS = type ? GET_CONTENT_WAIT_BUTTON_VI : GET_CONTENT_WAIT_BUTTON_EN;

        getButton->setText(TYPE_TRANS);
        createReceiverServer(window);
        peer = new PeerDiscovery(45454, window);
    });

    layout->addWidget(getButton, 0, 1);
}

void GetButton::createReceiverServer(QWidget *parent) {
    if (server == nullptr) {
        server = new QTcpServer(parent);
    }

    if (server && server->isListening()) {
        auto const DIALOG_TITLE = type ? DIALOG_INFO_TITLE_VI : DIALOG_INFO_TITLE_EN;
        auto const DIALOG_MESSAGE = type ? SERVER_ALREADY_ERR_VI : SERVER_ALREADY_ERR_EN;

        QMessageBox::information(parent, DIALOG_TITLE, DIALOG_MESSAGE);
        return;
    }

    if (!server->listen(QHostAddress::AnyIPv4, 8000)) {
        auto const DIALOG_TITLE = type ? DIALOG_ERROR_TITLE_VI : DIALOG_ERROR_TITLE_EN;
        auto const DIALOG_MESSAGE =
            type ? COULD_NOT_START_SERVER_ERR_VI : COULD_NOT_START_SERVER_ERR_EN;

        QMessageBox::critical(parent, DIALOG_TITLE, DIALOG_MESSAGE + server->errorString());
        server->deleteLater();
        server = nullptr;
        return;
    }

    connect(server, &QTcpServer::newConnection, this, [this]() {
        QTcpSocket *socket = server->nextPendingConnection();
        connect(socket, &QTcpSocket::readyRead, this, [socket]() {
            QApplication::clipboard()->setText(QString::fromUtf8(socket->readAll()));
            socket->deleteLater();
        });
    });
}

QTcpServer *GetButton::getServer() {
    if (server) {
        return server;
    }

    return nullptr;
}

void GetButton::resetServer() {
    server = nullptr;
}

QPushButton *GetButton::getConnectButton() const {
    return getButton;
}