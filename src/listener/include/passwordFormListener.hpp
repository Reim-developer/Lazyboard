#ifndef PASSWORD_FORM_LISTENER_HPP
#define PASSWORD_FORM_LISTENER_HPP
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <functional>
#include "../../core/include/enum.hpp"

using std::function;
using zclipboard::core::HashState;

namespace zclipboard::listener {
class PasswordFormListener : public QObject {
    Q_OBJECT

   public:
    void onSubmitPassword(QPushButton *submitButton, QLineEdit *passwordLine, QDialog *parent,
                          function<HashState()> lambda);

   signals:
    void loginResult(HashState hashState);
};
}  // namespace zclipboard::listener

#endif  // PASSWORD_FORM_LISTENER_HPP