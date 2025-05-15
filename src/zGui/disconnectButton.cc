#include "include/disconnectButton.hpp"
#include <QPushButton>

using zclipboard::zGui::DisconnectButton;
using zclipboard::zGui::DisconnectButtonWidget;

void DisconnectButton::addDisconnectButton(const DisconnectButtonWidget &params) {
    QPushButton *button = new QPushButton(params.parent);
    button->setText("Disconnect");
    params.layout->addWidget(button, 0, 4);
}