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
} ListenerDialogParameters;

class ListenerDialog : public QObject {
    Q_OBJECT

   private:
    void showPasswordMismatchDialog(QSettings *settings, QDialog *parent);

   public:
    void onChangePassword(const ListenerDialogParameters &params);
    void onSubmitPassword(const ListenerDialogParameters &params, QDialog *parent,
                          QPushButton *submitButton);
};
}  // namespace zclipboard::listener

#endif  // LISTENER_DIALOG_HPP