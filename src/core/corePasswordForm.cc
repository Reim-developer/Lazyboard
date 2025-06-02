#include "include/corePasswordForm.hpp"
#include <QDebug>
#include <string>

using std::function;
using std::string;
using zclipboard::core::CorePasswordForm;

auto CorePasswordForm::addPasswordFormListener(QLineEdit *passwordLine) -> function<void()> {
    // clang-format off
    const auto function = [passwordLine]() { 
        qDebug() << passwordLine->text();
    };
    // clang-format on

    return function;
}