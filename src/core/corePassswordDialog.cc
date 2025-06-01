#include "include/corePasswordDialog.hpp"
#include "../language/include/language.hpp"
#include "../zUtils/include/settings.hpp"
#include <QMessageBox>

using std::function;
using zclipboard::core::CorePasswordDialog;
using zclipboard::core::SubmitPasswordParams;

void CorePasswordDialog::showErrorDialog(C_STR title, C_STR msg, QDialog *parent) {
    QMessageBox::information(parent, title, msg);
}

function<void()> CorePasswordDialog::addShowPasswordListener(const ShowPasswordParams &params) {
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

    return function;
}

function<void()> CorePasswordDialog::addSubmitPasswordListener(const SubmitPasswordParams &params) {
    const auto function = [this, params]() {
        const auto passwordFieldValue1 = params.passwordInputField->text();
        const auto passswordFieldValue2 = params.passwordInputField2->text();

        const auto LANGUAGE_TYPE = params.settings->value(LANGUAGE_SETTING).toInt();
        const auto MSG_TITLE = LANGUAGE_TYPE ? DIALOG_ERROR_TITLE_VI : DIALOG_ERROR_TITLE_EN;

        if (passwordFieldValue1 != passswordFieldValue2) {
            const auto MSG_TEXT = LANGUAGE_TYPE ? PASSWORD_MISMATCH_VI : PASSWORD_MISMATCH_EN;

            showErrorDialog(MSG_TITLE, MSG_TEXT, params.parent);
            return;
        }

        if (passwordFieldValue1.isEmpty() || passswordFieldValue2.isEmpty()) {
            const auto MSG_TEXT = LANGUAGE_TYPE ? PASSWORD_EMPTY_VI : PASSWORD_EMPTY_EN;

            showErrorDialog(MSG_TITLE, MSG_TEXT, params.parent);

            return;
        }
    };

    return function;
}