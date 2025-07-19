#include "Include/SettingDialog.hpp"
#include "../Language/Include/Translate.hpp"
#include "../Utils/Include/Settings.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Utils/Include/Utils.hpp"
#include "../Language/Include/Language.hpp"
#include "Include/Window.hpp"
#include <QStringLiteral>
#include <QSettings>
#include <QIcon>
#include "../Core/Include/CoreSetting.hpp"

using ZClipboard::Core::SettingCore;
using ZClipboard::Core::SettingCoreParams;
using ZClipboard::Language::Translate;
using ZClipboard::Language::TransValue;
using ZClipboard::GUI::SettingButton;
using ZClipboard::AppUtils::Utils;

void SettingButton::SetupSettingButton(QMainWindow *window, QGridLayout *layout) {
    settingButton = new QPushButton(window);
    settingCore = new SettingCore();

    const auto function = [this, window]() {
        window->hide();
        showSettingDialog(window);
    };
    connect(settingButton, &QPushButton::clicked, this, function);

    layout->addWidget(settingButton, 0, 3);
}

void SettingButton::showSettingDialog(QMainWindow *parent) {
    settings = new QSettings(AUTHOR_NAME, APP_NAME);
    QDialog *dialog = new QDialog(parent);
    layout = new QGridLayout(dialog);

    QIcon icon = QIcon(ICON_PATH);
    constexpr int FIXED_WIDTH = 600;
    constexpr int FIXED_HEIGHT = 400;

    // clang-format off
    TransValue dialogValue {
        .LANGUAGE_EN = SETTING_DIALOG_EN, 
        .LANGUAGE_VI = SETTING_DIALOG_VI
    };
    // clang-format on

    const int LANGUAGE = settings->value(LANGUAGE_SETTING).toInt();
    const auto TYPE = Utils::languageTypeCast(LANGUAGE);

    Translate::translatorWidget(dialog, TYPE, dialogValue);

    // clang-format off
    const auto function = [parent]() {
        parent->show();
    };
    // clang-format on

    connect(dialog, &QDialog::finished, this, function);

    dialog->resize(FIXED_WIDTH, FIXED_HEIGHT);
    dialog->setWindowIcon(icon);
    dialog->setLayout(layout);
    addGui(layout, dialog);
    dialog->exec();
}

void SettingButton::addGui(QGridLayout *layout, QDialog *dialog) {
    autoHideCheckBox = new QCheckBox(dialog);
    autoNotificatonCheckBox = new QCheckBox(dialog);
    languageBox = new QComboBox(dialog);
    themeBox = new QComboBox(dialog);
    languageDescription = new QLabel(dialog);
    themeDescription = new QLabel(dialog);
    setPasswordButton = new QPushButton(dialog);

    const int LANGUAGE = settings->value(LANGUAGE_SETTING).toInt();
    const auto TYPE = Utils::languageTypeCast(LANGUAGE);

    bool isHide = settings->value(AUTO_HIDE_SETTING).toBool();
    bool isNotification = settings->value(AUTO_NOTIFICATION_SETTING).toBool();

    // clang-format off
    TransValue minimizeValue {
        .LANGUAGE_EN = MINIMIZE_CHECKBOX_EN,
        .LANGUAGE_VI = MINIMIZE_CHECKBOX_VI
    };

    TransValue notifiValue {
        .LANGUAGE_EN = NOTIFICATION_CHECKBOX_EN,
        .LANGUAGE_VI = NOTIFICATION_CHECKBOX_VI
    };

    TransValue setPasswordValue {
        .LANGUAGE_EN = SET_PASSWORD_EN,
        .LANGUAGE_VI = SET_PASSWORD_VI
    };
    // clang-format on

    autoHideCheckBox->setChecked(isHide);
    autoNotificatonCheckBox->setChecked(isNotification);

    addSettingCheckboxAction();
    addLanguageSectionAction(dialog);
    addThemeSectionAction();
    settingCore->onChangePassword(setPasswordButton, dialog);

    Translate::translatorWidget(autoHideCheckBox, TYPE, minimizeValue);
    Translate::translatorWidget(autoNotificatonCheckBox, TYPE, notifiValue);
    Translate::translatorWidget(setPasswordButton, TYPE, setPasswordValue);

    layout->addWidget(setPasswordButton, 3, 2);

    layout->addWidget(autoHideCheckBox, 0, 0);
    layout->addWidget(autoNotificatonCheckBox, 1, 0);

    layout->addWidget(languageBox, 2, 0);
    layout->addWidget(themeBox, 3, 0);

    layout->addWidget(languageDescription, 2, 1);
    layout->addWidget(themeDescription, 3, 1);
}

void SettingButton::addSettingCheckboxAction() {
    // clang-format off
    struct SettingCoreParams notifitionSetting {
        .settings = settings,
        .checkBox = autoNotificatonCheckBox,
    };

    struct SettingCoreParams hideSetting {
        .settings = settings,
        .checkBox = autoHideCheckBox,
    };
    // clang-format on

    settingCore->addHideSetting(hideSetting);
    settingCore->addNotificationSetting(notifitionSetting);
}

void SettingButton::addLanguageSectionAction(QDialog *dialog) {
    // clang-format off
    struct SettingCoreParams settingLanguageParams {
        .dialog = dialog,
        .settings = settings,
        .languageDescription = languageDescription,
        .themeDescription = themeDescription,
        .languageBox = languageBox,
        .themeBox = themeBox,
        .autoHideCheckBox = autoHideCheckBox,
        .autoNotificatonCheckBox = autoNotificatonCheckBox
    };
    // clang-format on
    settingCore->addLanguageSetting(settingLanguageParams);
    settingCore->onLanguageSettingChanged(settingLanguageParams);
}

void SettingButton::addThemeSectionAction() {
    // clang-format off
    struct SettingCoreParams settingThemeParams {
        .settings = settings,
        .themeDescription = themeDescription,
        .themeBox = themeBox
    };
    // clang-format on

    settingCore->addThemeSetting(settingThemeParams);
    settingCore->onThemeSettingChanged(settingThemeParams);
}

QPushButton *SettingButton::getSettingButton() {
    return settingButton;
}