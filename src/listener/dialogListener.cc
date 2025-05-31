#include "include/dialogListener.hpp"
#include "../language/include/language.hpp"
#include "../zUtils/include/settings.hpp"

using zclipboard::listener::ListenerDialog;

void ListenerDialog::onChangePassword(const changePasswordParameters &params) {
    const auto function = [params]() {
        const auto ECHO_MODE = params.passwordInputField->echoMode();
        const auto LANGUAGE_TYPE = params.settings->value(LANGUAGE_SETTING).toInt();

        // clang-format off
        const auto HIDE_PASSWORD_TEXT = LANGUAGE_TYPE ? PASSWORD_HIDE_BUTTON_VI : PASSWORD_HIDE_BUTTON_EN;
        const auto SHOW_PASSWORD_TEXT =  LANGUAGE_TYPE ? PASSWORD_SHOW_BUTTON_VI : PASSWORD_SHOW_BUTTON_EN;
        // clang-format on

        if (ECHO_MODE != params.passwordInputField->Password) {
            params.passwordInputField->setEchoMode(QLineEdit::Password);
            params.passwordInputField2->setEchoMode(QLineEdit::Password);

            params.showPasswordButton->setText(SHOW_PASSWORD_TEXT);
        } else {
            params.passwordInputField->setEchoMode(QLineEdit::Normal);
            params.passwordInputField2->setEchoMode(QLineEdit::Normal);

            params.showPasswordButton->setText(HIDE_PASSWORD_TEXT);
        }
    };

    connect(params.showPasswordButton, &QPushButton::clicked, this, function);
}