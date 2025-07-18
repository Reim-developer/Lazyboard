#include "Include/ListenerDisconnect.hpp"
#include "../Utils/Include/Settings.hpp"
#include "../Language/Include/Language.hpp"
#include <QMessageBox>

using ZClipboard::Listener::ListenerDisconnect;

VOID_FUNC ListenerDisconnect::TryGetListener() {
    const auto Function = [this]() -> void {
        auto settings = this 
            ->  Impl
            ->  setting;

        auto connectButton = this
            ->  Impl
            ->  toolkit
            ->  GetConnectButton();
    
        auto server = this
            ->  Impl
            ->  getButton
            ->  GetNetworkState()
            ->  GetServer();
            
        auto parent = this
            ->  Impl
            ->  windowParent;

        const int LANGUAGE_TYPE = settings->value(LANGUAGE_SETTING).toInt();

        if (!server || !server->isListening()) {
            const auto DIALOG_ERR_TITLE = LANGUAGE_TYPE ? DIALOG_INFO_TITLE_VI : DIALOG_INFO_TITLE_EN;
            const auto DIALOG_ERR_MSG = LANGUAGE_TYPE ? NO_ACTIVE_CONNECT_ERR_VI : NO_ACTIVE_CONNECT_ERR_EN;

            QMessageBox::information(parent, DIALOG_ERR_TITLE, DIALOG_ERR_MSG);
            return;
        } else {
            server->close();
            server->deleteLater();

            const auto DIALOG_TITLE = LANGUAGE_TYPE ? DIALOG_INFO_TITLE_VI : DIALOG_INFO_TITLE_EN;
            const auto DIALOG_MSG = LANGUAGE_TYPE ? DISCONNECT_SUCCESS_MSG_VI : DISCONNECT_SUCCESS_MSG_EN;

            QMessageBox::information(parent, DIALOG_TITLE, DIALOG_MSG);
        }

        this
            ->  Impl
            ->  getButton
            ->  ResetServer();
        const auto BUTTON_TEXT = LANGUAGE_TYPE ? GET_CONTENT_BUTTON_VI : GET_CONTENT_BUTTON_EN;

        connectButton->setText(BUTTON_TEXT);

    };

    return Function;
}