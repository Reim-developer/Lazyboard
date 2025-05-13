#ifndef GET_BUTTON_HPP
#define GET_BUTTON_HPP
#include <QWidget>
#include <QObject>
#include <QGridLayout>
#include <QPushButton>
#include <QtNetwork/QTcpServer>
#include "../../znetwork/include/PeerDiscovery.hpp"

using zclipboard::znetwork::PeerDiscovery;

namespace zclipboard::zGui {
class GetButton : public QObject {
    Q_OBJECT

   public:
    void addGetButton(QWidget *window, QGridLayout *layout);
    void createReceiverServer(QWidget *window);

   private:
    QPushButton *getButton;
    QTcpServer *server;
    PeerDiscovery *peer;
};
}  // namespace zclipboard::zGui

#endif  // GET_BUTTON_HPP