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

    connect(getButton, &QPushButton::clicked, this,
            [this, window]() { createReceiverServer(window); });

    layout->addWidget(getButton, 0, 1);
}

void GetButton::createReceiverServer(QWidget *parent) {
    QTcpServer *server = new QTcpServer(parent);

    if (!server->listen(QHostAddress::AnyIPv4, 8000)) {
        QMessageBox::critical(
            parent, QStringLiteral("Error"),
            QString("Could not start server with error: %1").arg(server->errorString()));
        return;
    }

    connect(server, &QTcpServer::newConnection, parent, [server, parent]() {
        QTcpSocket *socket = server->nextPendingConnection();

        connect(socket, &QTcpSocket::readyRead, parent, [socket]() {
            QByteArray data = socket->readAll();
            QApplication::clipboard()->setText(QString::fromUtf8(data));

            socket->deleteLater();
        });
    });
}