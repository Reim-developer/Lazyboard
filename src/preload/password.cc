#include "include/password.hpp"
#include "../zUtils/include/settings.hpp"
#include "../zUtils/include/config.hpp"
#include "../zUtils/include/zUtils.hpp"
#include "../language/include/language.hpp"
#include "../listener/include/passwordFormListener.hpp"
#include <QSettings>
#include <QDialog>
#include <memory>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>

// clang-format off
/*
* Flag for debug only.
* Use with CMake:
* -DZ_DEBUG=1
*/
#if defined(Z_DEBUG)
    #include <QDebug>
#endif
// clang-format on

using std::make_unique;
using std::unique_ptr;
using zclipboard::listener::PasswordFormListener;
using zclipboard::preload::PreloadPassword;

void PreloadPassword::setLoginFormGui(const QSettings &settings) {
    unique_ptr<QDialog> dialog = make_unique<QDialog>();
    unique_ptr<QLineEdit> passwordField = make_unique<QLineEdit>();
    unique_ptr<QPushButton> loginButton = make_unique<QPushButton>();
    unique_ptr<QLabel> loginDescription = make_unique<QLabel>();
    unique_ptr<QGridLayout> layout = make_unique<QGridLayout>();
    unique_ptr<PasswordFormListener> passwordFormListener = make_unique<PasswordFormListener>();

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
    passwordFormListener->onSubmitPassword(loginButton.get(), passwordField.get(), dialog.get());

    layout->addWidget(loginDescription.get(), 0, 0);
    layout->addWidget(passwordField.get(), 1, 0);
    layout->addWidget(loginButton.get(), 1, 2);

    dialog->setLayout(layout.get());
    dialog->setWindowTitle(FORM_TITLE);
    dialog->setMinimumSize(500, 100);
    dialog->exec();
}

auto PreloadPassword::showLoginForm() -> LoginState {
    QSettings settings(AUTHOR_NAME, APP_NAME);

    if (!zUtils::hasSetting(PASSWORD_SETTING)) {
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
            setLoginFormGui(settings);

        #else

            setLoginFormGui(settings);

        #endif
        // clang-format on

        return LoginState::LOGIN_FAILED;
    }

    return LoginState::LOGIN_NOT_SET;
}