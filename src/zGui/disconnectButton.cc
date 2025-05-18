#include "include/disconnectButton.hpp"
#include <QPushButton>
#include <QMessageBox>
#include <QStringLiteral>

using zclipboard::zGui::DisconnectButton;
using zclipboard::zGui::DisconnectButtonWidget;

void DisconnectButton::addDisconnectButton(const DisconnectButtonWidget &params) {
    button = new QPushButton(params.parent);
    button->setText("Disconnect");
    params.layout->addWidget(button, 0, 4);

    disconnectFromHost({.parent = params.parent, .button = button, .getButton = params.getButton});
}

void DisconnectButton::disconnectFromHost(const DisconnectButtonWidget &params) {
    connect(params.button, &QPushButton::clicked, this, [this, params]() {
        auto server = params.getButton->getServer();

        if (!server || !server->isListening()) {
            QMessageBox::information(params.parent, QStringLiteral("Information"),
                                     QStringLiteral("No active connection to disconnect."));
            return;
        }

        server->close();
        server->deleteLater();
        params.getButton->resetServer();

        QMessageBox::information(params.parent, QStringLiteral("Information"),
                                 QStringLiteral("Disconnect successfully"));
        params.getButton->getConnectButton()->setText(
            QStringLiteral("Get clipboard from another device"));
    });
}

QPushButton *DisconnectButton::getDisconnectButton() {
    return button;
}