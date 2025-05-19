#ifndef DISCONNECT_BUTTON_HPP
#define DISCONNECT_BUTTON_HPP
#include <QObject>
#include <QPushButton>
#include <QGridLayout>
#include <QtNetwork/QTcpServer>
#include <QSettings>
#include "getButton.hpp"

using zclipboard::zGui::GetButton;

namespace zclipboard::zGui {

struct DisconnectButtonWidget {
    QWidget *parent;
    QGridLayout *layout;
    QPushButton *button;
    GetButton *getButton;
};

class DisconnectButton : public QObject {
    Q_OBJECT

   public:
    void addDisconnectButton(const DisconnectButtonWidget &params);
    QPushButton *getDisconnectButton();

   private:
    void disconnectFromHost(const DisconnectButtonWidget &params);

   private:
    QSettings *settings;
    QPushButton *button;
    QTcpServer *server;
};
}  // namespace zclipboard::zGui

#endif  // DISCONNECT_BUTTON_HPP