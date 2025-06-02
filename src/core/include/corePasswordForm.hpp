#ifndef CORE_PASSWORD_FORM_HPP
#define CORE_PASSWORD_FORM_HPP

#include <QLineEdit>
#include <functional>

using std::function;

namespace zclipboard::core {
class CorePasswordForm {
   public:
    auto addPasswordFormListener(QLineEdit *passwordLine) -> function<void()>;
};
}  // namespace zclipboard::core

#endif  // CORE_PASSWORD_FORM_HPP