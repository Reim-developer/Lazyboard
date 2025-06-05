#ifndef CORE_PASSWORD_FORM_HPP
#define CORE_PASSWORD_FORM_HPP
#include <QDialog>
#include <QLineEdit>
#include <functional>
#include "enum.hpp"

using std::function;
using zclipboard::core::HashState;

namespace zclipboard::core {
class CorePasswordForm {
   public:
    function<void()> addPasswordFormListener(QLineEdit *passwordLine, QDialog *parent);
};
}  // namespace zclipboard::core

#endif  // CORE_PASSWORD_FORM_HPP