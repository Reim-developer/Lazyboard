#include "include/dialogListener.hpp"
#include "../language/include/language.hpp"
#include "../zUtils/include/settings.hpp"
#include <QMessageBox>

using zclipboard::listener::ListenerDialog;

void ListenerDialog::showPasswordMismatchDialog(QSettings *settings, QDialog *parent) {
    const auto LANGUAGE_TYPE = settings->value(LANGUAGE_SETTING).toInt();
    const auto MSG_TITLE = LANGUAGE_TYPE ? DIALOG_ERROR_TITLE_VI : DIALOG_ERROR_TITLE_EN;
    const auto MSG_TEXT = LANGUAGE_TYPE ? PASSWORD_MISMATCH_VI : PASSWORD_MISMATCH_EN;

    QMessageBox::information(parent, MSG_TITLE, MSG_TEXT);
}

void ListenerDialog::onChangePassword(const ListenerDialogParameters &params) {
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

void ListenerDialog::onSubmitPassword(const ListenerDialogParameters &params, QDialog *parent,
                                      QPushButton *submitButton) {
    const auto functionSubmit = [this, params, parent]() {
        const auto passwordFieldValue1 = params.passwordInputField->text();
        const auto passswordFieldValue2 = params.passwordInputField2->text();

        if (passwordFieldValue1 != passswordFieldValue2) {
            showPasswordMismatchDialog(params.settings, parent);
        }
    };

    connect(submitButton, &QPushButton::clicked, this, functionSubmit);
}