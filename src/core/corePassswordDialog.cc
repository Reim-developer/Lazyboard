#include <sodium/core.h>
#include "include/corePasswordDialog.hpp"
#include "../language/include/language.hpp"
#include "../zUtils/include/settings.hpp"
#include "../encryption/c/include/argon2id.h"
#include "../zUtils/include/config.hpp"
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QStandardPaths>

using std::function;
using zclipboard::core::CorePasswordDialog;
using zclipboard::core::SubmitPasswordParams;

void CorePasswordDialog::showDialog(C_STR title, C_STR msg, QDialog *parent) {
    QMessageBox::information(parent, title, msg);
}

void CorePasswordDialog::savePasswordHash(C_STR password, QSettings *settings, QDialog *parent) {
    /*
    * Expands to:
    * $HOME/.config on Linux.
    */
    auto const constexpr APP_CONFIG_FOLDER = APP_NAME;
    auto const constexpr PATH_SLASH = '/';
    const constexpr char HASH_FILE[] = "Hash.bin";
    const auto CONFIG_DIRECTORY = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);

    QDir directory(CONFIG_DIRECTORY + PATH_SLASH + APP_CONFIG_FOLDER);
    QString hashPasswordLocation;

    if (!directory.exists()) {
        // clang-format off
        #if defined(Z_DEBUG)
            qDebug() << directory.absolutePath() << " Is not exists.";

            const auto STATUS_OK = directory.mkdir(directory.absolutePath());
            if(!STATUS_OK) {
                qDebug() << "Could not create directory";
                const auto LANGUAGE_TYPE = settings->value(LANGUAGE_SETTING).toInt();

                const auto TITLE_DIALOG = LANGUAGE_TYPE ? DIALOG_ERROR_TITLE_VI : DIALOG_ERROR_TITLE_EN;
                const auto TITLE_MSG = LANGUAGE_TYPE ? HASH_FAILED_MSG_VI : HASH_FAILED_MSG_EN;

                showDialog(TITLE_DIALOG, TITLE_MSG, parent);

                return;
            }
            qDebug() << "Create directory successfully";
            qDebug() << "Absolute path: " << directory.absolutePath();
        
        #else
            const auto STATUS_OK = directory.mkdir(directory.absolutePath());

            if(!STATUS_OK) {
                const auto LANGUAGE_TYPE = settings->value(LANGUAGE_SETTING).toInt();
                const auto TITLE_DIALOG = LANGUAGE_TYPE ? DIALOG_ERROR_TITLE_VI : DIALOG_ERROR_TITLE_EN;
                const auto TITLE_MSG = LANGUAGE_TYPE ? HASH_FAILED_MSG_VI : HASH_FAILED_MSG_EN;

                showDialog(TITLE_DIALOG, TITLE_MSG, parent);
            }

        #endif
        // clang-format on
    }

    /*
    * Linux:
    * Expands to: $HOME/.config/$APP_NAME/$HASH_FILE
    */
    hashPasswordLocation = directory.absolutePath() + PATH_SLASH + HASH_FILE;

    QFile hashPasswordPath(hashPasswordLocation);

    if (!hashPasswordPath.exists()) {
        // clang-format off
        /*
        * Debug flag only.
        * Use with CMake flag:
        * -DZ_DEBUG=1
        */
        #if defined(Z_DEBUG)
            qDebug() <<  hashPasswordLocation << "is not exists.";
            qDebug() << hashPasswordLocation << "Generate now";

            const auto STATUS_OK = hashPasswordPath.open(QIODevice::WriteOnly);
            if(!STATUS_OK) {
                qDebug() << "Write password hash failed:";
                qDebug() << hashPasswordPath.errorString();
                
                const auto LANGUAGE_TYPE = settings->value(LANGUAGE_SETTING).toInt();

                const auto TITLE_DIALOG = LANGUAGE_TYPE ? DIALOG_ERROR_TITLE_VI : DIALOG_ERROR_TITLE_EN;
                const auto TITLE_MSG = LANGUAGE_TYPE ? HASH_FAILED_MSG_VI : HASH_FAILED_MSG_EN;

                showDialog(TITLE_DIALOG, TITLE_MSG, parent);
                hashPasswordPath.close();

                return;
            }
       
            const auto BYTE = hashPasswordPath.write(password);
            qDebug() << "Write successfully.";
            qDebug() << "Length:" << BYTE;

            hashPasswordPath.close();
        #else

            hashPasswordPath.open(QIODevice::WriteOnly);
            hashPasswordPath.write(password);   
            hashPasswordPath.close();
        #endif

    }

    #if defined(Z_DEBUG)
        hashPasswordPath.open(QIODevice::WriteOnly);
        hashPasswordPath.write(password);
        hashPasswordPath.close();

        qDebug() << "Write password successfully";
        qDebug() << "Password Hash:";
        qDebug() << password;
        qDebug() << "Hash Password Path: " <<  hashPasswordLocation;

    #else

        hashPasswordPath.open(QIODevice::WriteOnly);
        hashPasswordPath.write(password);
        hashPasswordPath.close();
    
    #endif

    // clang-format on
}

void CorePasswordDialog::setPasswordHash(C_STR password, QSettings *settings, QDialog *parent) {
    // clang-format off
    #if defined(Z_DEBUG)
        static bool init = false;
        if(!init) {
            const int STATUS = sodium_init();
            if(STATUS != 0) {
                qDebug() << "Could not init sodium";
            }

            init = true;
        }    
    #else

        static bool init = false;
        if(!init) {
            const int STATUS = sodium_init();
            init = true;
        }
    #endif
    // clang-format on

    char hashed[256];
    const auto HASH_STATUS = hash_password(password, hashed);

    if (HASH_STATUS == MEMORY_ERROR) {
        const auto LANGUAGE_TYPE = settings->value(LANGUAGE_SETTING).toInt();

        const auto MSG_TITLE = LANGUAGE_TYPE ? DIALOG_ERROR_TITLE_VI : DIALOG_ERROR_TITLE_EN;
        const auto MSG_TEXT = LANGUAGE_TYPE ? HASH_OUTMEMORY_ERR_VI : HASH_OUTMEMORY_ERR_EN;

        showDialog(MSG_TITLE, MSG_TEXT, parent);

        return;
    }

    if (HASH_STATUS == ENCRYPT_OK) {
        const auto LANGUAGE_TYPE = settings->value(LANGUAGE_SETTING).toInt();

        const auto MSG_TITLE = LANGUAGE_TYPE ? DIALOG_INFO_TITLE_VI : DIALOG_INFO_TITLE_EN;
        const auto MSG_TEXT = LANGUAGE_TYPE ? HASH_SUCCESS_MSG_VI : HASH_SUCCESS_MSG_EN;

        showDialog(MSG_TITLE, MSG_TEXT, parent);
    }

    settings->setValue(PASSWORD_SETTING, PASSWORD_SET);
    savePasswordHash(hashed, settings, parent);
}

function<void()> CorePasswordDialog::addShowPasswordListener(const ShowPasswordParams &params) {
    const auto function = [params]() {
        const auto ECHO_MODE = params.passwordInputField->echoMode();
        const auto LANGUAGE_TYPE = params.settings->value(LANGUAGE_SETTING).toInt();

        // clang-format off
        const auto HIDE_PASSWORD_TEXT = LANGUAGE_TYPE ? PASSWORD_HIDE_BUTTON_VI : PASSWORD_HIDE_BUTTON_EN;
        const auto SHOW_PASSWORD_TEXT =  LANGUAGE_TYPE ? PASSWORD_SHOW_BUTTON_VI : PASSWORD_SHOW_BUTTON_EN;
        // clang-format on

        if (ECHO_MODE != params.passwordInputField->Password) {
            params.passwordInputField->setEchoMode(QLineEdit::Password);
            params.passwordInputField2->setEchoMode(QLineEdit::Password);

            params.showPasswordButton->setText(SHOW_PASSWORD_TEXT);
        } else {
            params.passwordInputField->setEchoMode(QLineEdit::Normal);
            params.passwordInputField2->setEchoMode(QLineEdit::Normal);

            params.showPasswordButton->setText(HIDE_PASSWORD_TEXT);
        }
    };

    return function;
}

function<void()> CorePasswordDialog::addSubmitPasswordListener(const SubmitPasswordParams &params) {
    const auto function = [this, params]() {
        const auto passwordFieldValue1 = params.passwordInputField->text();
        const auto passswordFieldValue2 = params.passwordInputField2->text();

        const auto LANGUAGE_TYPE = params.settings->value(LANGUAGE_SETTING).toInt();
        const auto MSG_TITLE = LANGUAGE_TYPE ? DIALOG_ERROR_TITLE_VI : DIALOG_ERROR_TITLE_EN;

        if (passwordFieldValue1 != passswordFieldValue2) {
            const auto MSG_TEXT = LANGUAGE_TYPE ? PASSWORD_MISMATCH_VI : PASSWORD_MISMATCH_EN;

            showDialog(MSG_TITLE, MSG_TEXT, params.parent);
            return;
        }

        if (passwordFieldValue1.isEmpty() || passswordFieldValue2.isEmpty()) {
            const auto MSG_TEXT = LANGUAGE_TYPE ? PASSWORD_EMPTY_VI : PASSWORD_EMPTY_EN;

            showDialog(MSG_TITLE, MSG_TEXT, params.parent);

            return;
        }

        const auto PASSWORD = passwordFieldValue1.toUtf8().constData();
        setPasswordHash(PASSWORD, params.settings, params.parent);
    };

    return function;
}