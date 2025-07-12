#include "Include/PreloadPassword.hpp"
#include "../Utils/Include/Settings.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Utils/Include/Utils.hpp"
#include "../Language/Include/Language.hpp"
#include "../Listener/Include/ListenerPasswordForm.hpp"
#include "../Core/Include/CorePasswordForm.hpp"
#include <QSettings>
#include <QDialog>
#include <memory>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

/*
* Flag for debug only.
* Use with CMake:
* -DZ_DEBUG=1
*/
#if defined(Z_DEBUG)
    #include <QDebug>
#endif

using std::make_unique;
using std::unique_ptr;
using ZClipboard::Core::CorePasswordForm;
using ZClipboard::Listener::PasswordFormListener;
using ZClipboard::Preload::PreloadPassword;
using ZClipboard::AppUtils::Utils;

int PreloadPassword::setLoginFormGui(const QSettings &settings) {
    dialog = make_unique<QDialog>();
    unique_ptr<QLineEdit> passwordField = make_unique<QLineEdit>();
    unique_ptr<QPushButton> loginButton = make_unique<QPushButton>();
    unique_ptr<QLabel> loginDescription = make_unique<QLabel>();
    unique_ptr<QGridLayout> layout = make_unique<QGridLayout>();
    unique_ptr<PasswordFormListener> passwordFormListener = make_unique<PasswordFormListener>();
    unique_ptr<CorePasswordForm> corePasswordForm = make_unique<CorePasswordForm>();

    // clang-format off
    const auto LANGUAGE_TYPE = settings.value(LANGUAGE_SETTING).toInt();
    const auto FORM_TITLE = LANGUAGE_TYPE ? LOGIN_FORM_TITLE_VI : LOGIN_FORM_TITLE_EN;
    const auto LOGIN_BUTTON_TEXT = LANGUAGE_TYPE ? SUBMIT_BUTTON_VI : SUBMIT_BUTTON_EN;
    const auto LABEL_DESCRIPTION = LANGUAGE_TYPE ? LOGIN_FORM_DESCRIPTION_VI : LOGIN_FORM_DESCRIPTION_EN;
    // clang-format on

    loginButton->setText(LOGIN_BUTTON_TEXT);
    loginDescription->setText(LABEL_DESCRIPTION);
    passwordField->setEchoMode(QLineEdit::Password);

    /*
    * Connect event
    */
    // clang-format off
    const auto function = corePasswordForm->addPasswordFormListener(passwordField.get(), dialog.get());
    connect(passwordFormListener.get(), &PasswordFormListener::loginResult, this, &PreloadPassword::onLoginSubmit);
    passwordFormListener->onSubmitPassword(loginButton.get(), passwordField.get(), dialog.get(), function);
    // clang-format on

    layout->addWidget(loginDescription.get(), 0, 0);
    layout->addWidget(passwordField.get(), 1, 0);
    layout->addWidget(loginButton.get(), 1, 2);

    dialog->setLayout(layout.get());
    dialog->setWindowTitle(FORM_TITLE);
    dialog->setMinimumSize(500, 100);

    const auto RESULT_CODE = dialog->exec();

    return RESULT_CODE;
}

void PreloadPassword::onLoginSubmit(HashState hashState) {
    switch (hashState) {
        case HashState::HASH_OK:
            // clang-format off
            #if defined(Z_DEBUG)
                qDebug() << "Hash match. Close dialog";
            #endif
            // clang-format on
            dialog->accept();

        /*
        * Otherwise will be implement in 'CorePasswordForm'
        */
        case Core::HashState::HASH_MISMATCH:
        case Core::HashState::DELETED:
        case Core::HashState::MODIFIED:
        case Core::HashState::HASH_FILE_NOT_FOUND:
        case Core::HashState::HASH_FILE_EMPTY:
            break;
    }
}

auto PreloadPassword::showLoginForm() -> LoginState {
    QSettings settings(AUTHOR_NAME, APP_NAME);

    if (!Utils::hasSetting(PASSWORD_SETTING)) {
        return LoginState::LOGIN_NOT_SET;
    }

    const auto IS_PASSWORD_SET = settings.value(PASSWORD_SETTING).toBool();

    if (IS_PASSWORD_SET) {
        // clang-format off
        /*
        * Flag for debug only.
        * Use with CMake:
        * -DZ_DEBUG=1
        */
        #if defined(Z_DEBUG)
            qDebug() << "Password setting detect. Show login dialog now.";
            const auto LOGIN_STATUS = setLoginFormGui(settings);

            if(LOGIN_STATUS == QDialog::Accepted) {
                return LoginState::LOGIN_OK;
            } 

        #else

            const auto LOGIN_STATUS = setLoginFormGui(settings);

            if(LOGIN_STATUS == QDialog::Accepted) {
                return LoginState::LOGIN_OK;
            } 

        #endif
        // clang-format on

        return LoginState::LOGIN_FAILED;
    }

    return LoginState::LOGIN_NOT_SET;
}