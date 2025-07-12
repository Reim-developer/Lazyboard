#include "Include/CorePasswordForm.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Utils/Include/Settings.hpp"
#include "../Language/Include/Language.hpp"
#include "../Encryption/C_Lib/Include/Argon2id.h"
#include "Include/Enum.hpp"

// clang-format off
//
// Debug flag only
// Use with CMake flag:
// DZ_DEBUG=1
//
#if defined(Z_DEBUG)
    #include <QDebug>
#endif
// clang-format on

#include <QStandardPaths>
#include <QFile>
#include <QSettings>
#include <QMessageBox>

using std::function;
using std::string;
using ZClipboard::Core::CorePasswordForm;
using ZClipboard::Core::HashState;

function<HashState()> CorePasswordForm::addPasswordFormListener(QLineEdit *passwordLine,
                                                                QDialog *parent) {
    const auto function = [passwordLine, parent]() -> HashState {
        auto const constexpr APP_CONFIG_FOLDER = APP_NAME;
        const constexpr char PATH_SLASH = '/';
        const constexpr char HASH_FILE_NAME[] = "Hash.bin";
        QSettings settings(AUTHOR_NAME, APP_NAME, parent);

        /*
        * Expands to:
        * $HOME/.config on Linux.
        */
        const auto HASH_FILE_DIR = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
        const auto HASH_FILE_ABSOLUTE_PATH =
            HASH_FILE_DIR + PATH_SLASH + APP_CONFIG_FOLDER + PATH_SLASH + HASH_FILE_NAME;

        // clang-format off
        //
        // Debug flag only
        // Use with CMake flag:
        // DZ_DEBUG=1
        //
        #if defined(Z_DEBUG)
            qDebug() << "Current Hash File:";
            qDebug() << HASH_FILE_ABSOLUTE_PATH;

        #endif
        // clang-format on

        QFile hashFile(HASH_FILE_ABSOLUTE_PATH);
        const auto LANGUAGE_TYPE = settings.value(LANGUAGE_SETTING).toInt();
        const auto DIALOG_TITLE = LANGUAGE_TYPE ? DIALOG_ERROR_TITLE_VI : DIALOG_ERROR_TITLE_EN;

        if (!hashFile.exists()) {
            const auto DIALOG_MSG = LANGUAGE_TYPE ? HASH_FILE_NOT_FOUND_VI : HASH_FILE_NOT_FOUND_EN;

            QMessageBox::critical(parent, DIALOG_TITLE, DIALOG_MSG);
            return HashState::HASH_FILE_NOT_FOUND;
        }

        hashFile.open(QIODevice::ReadOnly);
        const auto HASH_FILE_CONTENT = hashFile.readAll().toStdString();
        hashFile.close();

        if (HASH_FILE_CONTENT.empty()) {
            const auto DIALOG_MSG = LANGUAGE_TYPE ? HASH_FILE_EMPTY_VI : HASH_FILE_EMPTY_EN;

            QMessageBox::critical(parent, DIALOG_TITLE, DIALOG_MSG);
            return HashState::HASH_FILE_EMPTY;
        }

        const auto PASSWORD = passwordLine->text().toStdString();
        const auto STATUS = is_hash_matches(HASH_FILE_CONTENT.c_str(), PASSWORD.c_str());

        if (STATUS == HASH_MISMATCH) {
            const auto DIALOG_MSG = LANGUAGE_TYPE ? PASSWORD_MISMATCH_VI : PASSWORD_MISMATCH_EN;

            QMessageBox::critical(parent, DIALOG_TITLE, DIALOG_MSG);

            return HashState::HASH_MISMATCH;
        }

        return HashState::HASH_OK;
    };

    return function;
}
