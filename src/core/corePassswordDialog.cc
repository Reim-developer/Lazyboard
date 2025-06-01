#include <sodium/core.h>
#include "include/corePasswordDialog.hpp"
#include "../language/include/language.hpp"
#include "../zUtils/include/settings.hpp"
#include "../zUtils/include/zUtils.hpp"
#include "../encryption/c/include/argon2id.h"
#include <QMessageBox>
#include <QDir>
#include <QFile>

using std::function;
using zclipboard::core::CorePasswordDialog;
using zclipboard::core::SubmitPasswordParams;

void CorePasswordDialog::showDialog(C_STR title, C_STR msg, QDialog *parent) {
    QMessageBox::information(parent, title, msg);
}

void CorePasswordDialog::savePasswordHash(C_STR password, QSettings *settings) {
    const auto CACHE_PATH = zUtils::getCachePath();
    const auto HASH_FILE_LOCATION = CACHE_PATH + PATH_SLASH + Z_ENCRYPT_FOLDER;
    const auto ENCRYPTION_FILE_PATH = HASH_FILE_LOCATION + PATH_SLASH + HASH_FILE_NAME;

    QDir directory;
    // clang-format off
    #if defined(Z_DEBUG)
        qDebug() << HASH_FILE_LOCATION;
        qDebug() << ENCRYPTION_FILE_PATH;
    #endif
    // clang-format on

    if (!directory.exists(HASH_FILE_LOCATION)) {
        // clang-format off
        /*
        * Debug macro, use with CMake flag:
        * -DZ_DEBUG=1
        */
        QDir newDirectory;
        #if defined(Z_DEBUG)
            const auto result = newDirectory.mkpath(HASH_FILE_LOCATION);
            qDebug() << "Cache Path Directory: " << CACHE_PATH;
            qDebug() << "Hash File Location: " << HASH_FILE_LOCATION;
            
            if(!result) {
                qDebug() << "Could not create path directory";
            }
            qDebug() << "Create directory successfully.";
            
            QFile encryptionFile(ENCRYPTION_FILE_PATH);
            if(!encryptionFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                qDebug() << "Could not open and write file.";
                qDebug() << encryptionFile.errorString();
            }

            qDebug() << "Created file successfully.";
            encryptionFile.close();

        #else
            newDirectory.mkpath(HASH_FILE_LOCATION);
            QFile encryptionFile(ENCRYPTION_FILE_PATH);

            encryptionFile.open(QIODevice::WriteOnly | QIODevice::Truncate);

            encryptionFile.write(password);
            encryptionFile.close();
        #endif
        // clang-format on
    }

    QFile encryptionFile(ENCRYPTION_FILE_PATH);

    encryptionFile.open(QIODevice::WriteOnly | QIODevice::Truncate);

    encryptionFile.write(password);
    encryptionFile.close();
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
    savePasswordHash(hashed, settings);
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