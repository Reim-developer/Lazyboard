#include "include/disconnectButton.hpp"
#include "../zUtils/include/config.hpp"
#include "../zUtils/include/settings.hpp"
#include "../language/include/language.hpp"
#include <QPushButton>
#include <QMessageBox>
#include <QStringLiteral>

using zclipboard::zGui::DisconnectButton;
using zclipboard::zGui::DisconnectButtonWidget;

void DisconnectButton::addDisconnectButton(const DisconnectButtonWidget &params) {
    button = new QPushButton(params.parent);
    params.layout->addWidget(button, 0, 4);

    disconnectFromHost({.parent = params.parent, .button = button, .getButton = params.getButton});
}

void DisconnectButton::disconnectFromHost(const DisconnectButtonWidget &params) {
    connect(params.button, &QPushButton::clicked, this, [this, params]() {
        settings = new QSettings(AUTHOR_NAME, APP_NAME);
        auto server = params.getButton->getServer();

        const int LANGUAGE_TYPE = settings->value(LANGUAGE_SETTING).toInt();

        if (!server || !server->isListening()) {
            const auto DIALOG_ERR_TITLE =
                LANGUAGE_TYPE ? DIALOG_INFO_TITLE_VI : DIALOG_INFO_TITLE_EN;
            const auto DIALOG_ERR_MSG =
                LANGUAGE_TYPE ? NO_ACTIVE_CONNECT_ERR_VI : NO_ACTIVE_CONNECT_ERR_EN;

            QMessageBox::information(params.parent, DIALOG_ERR_TITLE, DIALOG_ERR_MSG);
            return;
        }

        server->close();
        server->deleteLater();
        params.getButton->resetServer();

        const auto DIALOG_TITLE = LANGUAGE_TYPE ? DIALOG_INFO_TITLE_VI : DIALOG_INFO_TITLE_EN;
        const auto DIALOG_MSG =
            LANGUAGE_TYPE ? DISCONNECT_SUCCESS_MSG_VI : DISCONNECT_SUCCESS_MSG_EN;

        QMessageBox::information(params.parent, DIALOG_TITLE, DIALOG_MSG);

        const auto BUTTON_TEXT = LANGUAGE_TYPE ? GET_CONTENT_BUTTON_VI : GET_CONTENT_BUTTON_EN;
        params.getButton->getConnectButton()->setText(BUTTON_TEXT);
    });
}

QPushButton *DisconnectButton::getDisconnectButton() {
    return button;
}