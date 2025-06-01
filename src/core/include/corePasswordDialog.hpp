#ifndef CORE_PASSWORD_DIALOG_HPP
#define CORE_PASSWORD_DIALOG_HPP

#include <QPushButton>
#include <QLineEdit>
#include <QSettings>
#include <QDialog>
#include <functional>
#define C_STR const char *

using std::function;

namespace zclipboard::core {

typedef struct {
    QLineEdit *passwordInputField;
    QLineEdit *passwordInputField2;
    QSettings *settings;
    QDialog *parent;
} SubmitPasswordParams;

typedef struct {
    QLineEdit *passwordInputField;
    QLineEdit *passwordInputField2;
    QSettings *settings;
    QPushButton *showPasswordButton;
} ShowPasswordParams;

class CorePasswordDialog {
   private:
    void showErrorDialog(C_STR title, C_STR msg, QDialog *parent);

   public:
    function<void()> addSubmitPasswordListener(const SubmitPasswordParams &params);
    function<void()> addShowPasswordListener(const ShowPasswordParams &params);
};
}  // namespace zclipboard::core

#endif  // CORE_PASSWORD_DIALOG_HPP