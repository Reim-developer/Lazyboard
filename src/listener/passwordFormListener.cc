#include "include/passwordFormListener.hpp"
#include "../core/include/corePasswordForm.hpp"
#include <QByteArray>
#include <memory>

using std::make_unique;
using std::unique_ptr;
using zclipboard::core::CorePasswordForm;
using zclipboard::listener::PasswordFormListener;

void PasswordFormListener::onSubmitPassword(QPushButton *submitButton, QLineEdit *passwordLine) {
    unique_ptr<CorePasswordForm> corePasswordForm = make_unique<CorePasswordForm>();
    const auto function = corePasswordForm->addPasswordFormListener(passwordLine);

    // clang-format off
    connect(submitButton, &QPushButton::clicked, this, function);
    // clang-format on
}