#include "include/getButton.hpp"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>

using zclipboard::zGui::GetButton;

void GetButton::addGetButton(QWidget *window, QGridLayout *layout) {
    getButton = new QPushButton(window);
    getButton->setText("Get clipboard from another device");

    connect(getButton, &QPushButton::clicked, this, [this, window]() {
        getButton->setText("Waiting connection device..");
        createReceiverServer(window);
        peer = new PeerDiscovery(45454, window);
    });

    layout->addWidget(getButton, 0, 1);
}

void GetButton::createReceiverServer(QWidget *parent) {
    if (server && server->isListening()) {
        QMessageBox::information(parent, "Status", "Server is already running.");
        return;
    }

    server = new QTcpServer(parent);
    if (!server->listen(QHostAddress::AnyIPv4, 8000)) {
        QMessageBox::critical(parent, "Error", "Could not start server: " + server->errorString());
        server->deleteLater();
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