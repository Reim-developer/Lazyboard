#ifndef LISTENER_DIALOG_HPP
#define LISTENER_DIALOG_HPP
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QSettings>

namespace zclipboard::listener {

typedef struct {
    QPushButton *showPasswordButton;
    QLineEdit *passwordInputField;
    QLineEdit *passwordInputField2;
    QSettings *settings;
} changePasswordParameters;

class ListenerDialog : public QObject {
    Q_OBJECT

   public:
    void onChangePassword(const changePasswordParameters &params);
};
}  // namespace zclipboard::listener

#endif  // LISTENER_DIALOG_HPP