#include "include/ListenerDisconnect.hpp"
#include "../zUtils/include/settings.hpp"
#include "../language/include/language.hpp"
#include <QMessageBox>

using zclipboard::listener::ListenerDisconnect;

VOID_FUNC ListenerDisconnect::TryGetListener() {
    const auto Function = [this]() -> void {
        auto settings = this 
        ->  Impl
        ->  setting;

        auto getButton = this
        ->  Impl
        ->  getButton;
    
        auto server = getButton->getServer();

        auto parent = this
        ->  Impl
        ->  windowParent;

        const int LANGUAGE_TYPE = settings->value(LANGUAGE_SETTING).toInt();

        if (!server || !server->isListening()) {
            const auto DIALOG_ERR_TITLE = LANGUAGE_TYPE ? DIALOG_INFO_TITLE_VI : DIALOG_INFO_TITLE_EN;
            const auto DIALOG_ERR_MSG = LANGUAGE_TYPE ? NO_ACTIVE_CONNECT_ERR_VI : NO_ACTIVE_CONNECT_ERR_EN;

            QMessageBox::information(parent, DIALOG_ERR_TITLE, DIALOG_ERR_MSG);
            return;
        }

        server->close();
        server->deleteLater();
        getButton->resetServer();

        const auto DIALOG_TITLE = LANGUAGE_TYPE ? DIALOG_INFO_TITLE_VI : DIALOG_INFO_TITLE_EN;
        const auto DIALOG_MSG = LANGUAGE_TYPE ? DISCONNECT_SUCCESS_MSG_VI : DISCONNECT_SUCCESS_MSG_EN;

        QMessageBox::information(parent, DIALOG_TITLE, DIALOG_MSG);

        const auto BUTTON_TEXT = LANGUAGE_TYPE ? GET_CONTENT_BUTTON_VI : GET_CONTENT_BUTTON_EN;

        getButton
        ->  getConnectButton()
        ->  setText(BUTTON_TEXT);

    };

    return Function;
}