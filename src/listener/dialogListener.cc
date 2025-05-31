#include "include/dialogListener.hpp"
#include "../core/include/corePasswordDialog.hpp"
#include <QMessageBox>
#include <memory>

using std::make_unique;
using std::unique_ptr;
using zclipboard::core::CorePasswordDialog;
using zclipboard::core::ShowPasswordParams;
using zclipboard::core::SubmitPasswordParams;
using zclipboard::listener::ListenerDialog;

void ListenerDialog::onChangePassword(const ListenerDialogParameters &params) {
    // clang-format off
    ShowPasswordParams showPasswordParams {
        .passwordInputField = params.passwordInputField,
        .passwordInputField2 = params.passwordInputField2,
        .settings = params.settings,
        .showPasswordButton = params.showPasswordButton
    };
    // clang-format on
    unique_ptr<CorePasswordDialog> corePasswordDialog = make_unique<CorePasswordDialog>();
    const auto function = corePasswordDialog->addShowPasswordListener(showPasswordParams);

    connect(params.showPasswordButton, &QPushButton::clicked, this, function);
}

void ListenerDialog::onSubmitPassword(const ListenerDialogParameters &params, QDialog *parent,
                                      QPushButton *submitButton) {
    // clang-format off
    SubmitPasswordParams submitPasswordParams {
        .passwordInputField = params.passwordInputField,
        .passwordInputField2 = params.passwordInputField2,
        .settings = params.settings,
        .parent = parent
    };
    // clang-format on
    unique_ptr<CorePasswordDialog> corePasswordDialog = make_unique<CorePasswordDialog>();
    const auto function = corePasswordDialog->addSubmitPasswordListener(submitPasswordParams);

    connect(submitButton, &QPushButton::clicked, this, function);
}