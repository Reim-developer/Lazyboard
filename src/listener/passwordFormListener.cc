#include "include/passwordFormListener.hpp"
#include "../core/include/corePasswordForm.hpp"
using zclipboard::listener::PasswordFormListener;

void PasswordFormListener::onSubmitPassword(QPushButton *submitButton, QLineEdit *passwordLine,
                                            QDialog *parent, function<HashState()> lambda) {
    const auto function = [this, lambda]() {
        const auto LOGIN_RESULT = lambda();
        emit loginResult(LOGIN_RESULT);
    };

    connect(submitButton, &QPushButton::clicked, this, function);
}