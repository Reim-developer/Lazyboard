#ifndef PEER_DISCOVERY_HPP
#define PEER_DISCOVERY_HPP
#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QStringLiteral>

namespace zclipboard::znetwork {
class PeerDiscovery : public QObject {
    Q_OBJECT

   public:
    explicit PeerDiscovery(quint16 port = 45454, QObject *parent = nullptr);

   signals:
    void peerFound(const QString &ipAddress);

   private slots:
    void broadcastWrite();
    void handleIncomingMessage();
    void prepareDatagram();
    QString getLocalDeviceName() const;
    QString getLocalIPAddress() const;

   private:
    QString broadcast_msg;
    QUdpSocket socket;
    QHostAddress multicastGroup;
    quint16 port;
};
}  // namespace zclipboard::znetwork

#endif  // PEER_DISCOVERY_HPP