#ifndef PASSWORD_FORM_LISTENER_HPP
#define PASSWORD_FORM_LISTENER_HPP
#include <QObject>
#include <QPushButton>
#include <QLineEdit>

namespace zclipboard::listener {
class PasswordFormListener : public QObject {
   public:
    void onSubmitPassword(QPushButton *submitButton, QLineEdit *passwordLine);
};
}  // namespace zclipboard::listener

#endif  // PASSWORD_FORM_LISTENER_HPP