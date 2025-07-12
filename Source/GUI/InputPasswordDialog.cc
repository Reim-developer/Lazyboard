#include "Include/InputPasswordDialog.hpp"
#include "../Language/Include/Language.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Utils/Include/Settings.hpp"
#include "../Listener/Include/ListenerPasswordDialog.hpp"
#include <QSettings>
#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QSettings>

#if defined(Z_DEBUG)
    #include <QDebug>
#endif

using ZClipboard::Listener::ListenerDialog;
using ZClipboard::Listener::ListenerDialogParameters;
using ZClipboard::GUI::InputPasswordDialog;


void InputPasswordDialog::showInputPassword(QDialog *parent) {
    QDialog *dialog = new QDialog(parent);
    QSettings settings(AUTHOR_NAME, APP_NAME);

    const int LANGUAGUE_TYPE = settings.value(LANGUAGE_SETTING).toInt();
    const auto DIALOG_TITLE = LANGUAGUE_TYPE ? INPUT_PASSWORD_DIALOG_VI : INPUT_PASSWORD_DIALOG_EN;

    // clang-format off
    /*
    * Debug flag only.
    * Use with CMake: -DZ_DEBUG=1
    */
    #if defined(Z_DEBUG)
        qDebug() << "Current language setting: " << LANGUAGUE_TYPE;
        qDebug() << "Current dialog title: " << DIALOG_TITLE;
    #endif

    const auto function = [parent]() {
        parent->show();
    };
    // clang-format on

    connect(dialog, &QDialog::finished, this, function);

    setupGui(dialog);

    dialog->setWindowTitle(DIALOG_TITLE);
    dialog->resize(DIALOG_WIDTH, DIALOG_HEIGHT);
    dialog->exec();
}

void InputPasswordDialog::setupGui(QDialog *parent) {
    QGridLayout *layout = new QGridLayout(parent);
    QSettings *settings = new QSettings(AUTHOR_NAME, APP_NAME, parent);
    ListenerDialog *listenerDialog = new ListenerDialog();

    passwordInputField = new QLineEdit(parent);
    passwordInputField2 = new QLineEdit(parent);
    submitButton = new QPushButton(parent);
    showPasswordButton = new QPushButton(parent);

    // clang-format off
    ListenerDialogParameters listenerDialogParams {
        .showPasswordButton = showPasswordButton,
        .passwordInputField = passwordInputField,
        .passwordInputField2 = passwordInputField2,
        .settings = settings
    };
    listenerDialog->onChangePassword(listenerDialogParams);
    listenerDialog->onSubmitPassword(listenerDialogParams, parent, submitButton);

    const int LANGUAGE_TYPE = settings->value(LANGUAGE_SETTING).toInt();
    const auto TOOLTIP_TEXT = LANGUAGE_TYPE ? PASSWORD_FIELD_TOOLTIP_VI : PASSWORD_FIELD_TOOLTIP_EN;
    const auto SUBMIT_BUTTON_TEXT = LANGUAGE_TYPE ? PASSWORD_SUBMIT_BUTTON_VI : PASSWORD_SUBMIT_BUTTON_EN;
    const auto SHOW_PASSWORD_BUTTON_TEXT = LANGUAGE_TYPE ? PASSWORD_SHOW_BUTTON_VI : PASSWORD_SHOW_BUTTON_EN;
    // clang-format on

    passwordInputField->setToolTip(TOOLTIP_TEXT);
    passwordInputField->setEchoMode(QLineEdit::Password);

    passwordInputField2->setToolTip(TOOLTIP_TEXT);
    passwordInputField2->setEchoMode(QLineEdit::Password);

    submitButton->setText(SUBMIT_BUTTON_TEXT);
    showPasswordButton->setText(SHOW_PASSWORD_BUTTON_TEXT);

    layout->addWidget(passwordInputField, 0, 0);
    layout->addWidget(passwordInputField2, 1, 0);
    layout->addWidget(showPasswordButton, 0, 1);
    layout->addWidget(submitButton, 1, 1);
    parent->setLayout(layout);
}
