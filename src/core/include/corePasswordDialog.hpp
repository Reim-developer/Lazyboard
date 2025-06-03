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
    static inline const constexpr char HASH_FILE_NAME[] = "zClipboard.bin";
    static inline const constexpr char PATH_SLASH = '/';
    static inline const constexpr char Z_ENCRYPT_FOLDER[] = "zEncryption";
    static inline const constexpr bool PASSWORD_SET = true;

   private:
    void showDialog(C_STR title, C_STR msg, QDialog *parent);
    void setPasswordHash(C_STR password, QSettings *settings, QDialog *parent);
    void savePasswordHash(C_STR password, QSettings *settings, QDialog *parent);

   public:
    function<void()> addSubmitPasswordListener(const SubmitPasswordParams &params);
    function<void()> addShowPasswordListener(const ShowPasswordParams &params);
};
}  // namespace zclipboard::core

#endif  // CORE_PASSWORD_DIALOG_HPP