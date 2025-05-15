#ifndef DISCONNECT_BUTTON_HPP
#define DISCONNECT_BUTTON_HPP
#include <QObject>
#include <QPushButton>
#include <QGridLayout>

namespace zclipboard::zGui {

struct DisconnectButtonWidget {
    QWidget *parent;
    QGridLayout *layout;
};

class DisconnectButton : public QObject {
    Q_OBJECT

   public:
    void addDisconnectButton(const DisconnectButtonWidget &params);
};
}  // namespace zclipboard::zGui

#endif  // DISCONNECT_BUTTON_HPP