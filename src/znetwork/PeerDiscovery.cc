#include "include/PeerDiscovery.hpp"
#include <QByteArray>
#include <QTimer>
#include <QSysInfo>
#include <QtNetwork/QHostInfo>
#include <QtNetwork/QNetworkInterface>
#include <QVariant>

using zclipboard::znetwork::PeerDiscovery;

PeerDiscovery::PeerDiscovery(quint16 port, QObject *parent)
    : QObject(parent), port(port), multicastGroup(QHostAddress(QStringLiteral("224.0.0.1"))) {
    socket.bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress);
    socket.joinMulticastGroup(multicastGroup);
    socket.setSocketOption(QAbstractSocket::MulticastLoopbackOption, QVariant(false));

    connect(&socket, &QUdpSocket::readyRead, this, &PeerDiscovery::handleIncomingMessage);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PeerDiscovery::broadcastWrite);
    timer->start(2000);

    prepareDatagram();
    broadcastWrite();
}

void PeerDiscovery::prepareDatagram() {
    QString ipAddress = getLocalIPAddress();
    QString deviceName = getLocalDeviceName();

    broadcast_msg = QString("ZCLIPBOARD|%1|%2").arg(ipAddress).arg(deviceName);
}

void PeerDiscovery::broadcastWrite() {
    socket.writeDatagram(broadcast_msg.toUtf8(), multicastGroup, port);
}

void PeerDiscovery::handleIncomingMessage() {
    while (socket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket.pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        socket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString msg = QString::fromLatin1(datagram);

        if (msg.startsWith(QStringLiteral("ZCLIPBOARD|"))) {
            QStringList parts = msg.split('|');

            if (parts.size() >= 3) {
                QString ipAddress = parts[1];
                QString deviceName = parts[2];

                if (ipAddress != socket.localAddress().toString())
                    emit peerFound(QString("%1 | %2").arg(ipAddress).arg(deviceName));
            }
        }
    }
}

QString PeerDiscovery::getLocalIPAddress() const {
    QList<QHostAddress> list = QNetworkInterface::allAddresses();

    for (const QHostAddress &address : list) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol &&
            address != QHostAddress::LocalHost && !address.toString().startsWith("169.254")) {
            return address.toString();
        }
    }

    return "Unknown IP Address";
}

QString PeerDiscovery::getLocalDeviceName() const {
    QString name = QSysInfo::machineHostName();

    if (name.isEmpty()) name = QHostInfo::localHostName();
    if (name.isEmpty()) name = QStringLiteral("Unknown Device");

    return name;
}