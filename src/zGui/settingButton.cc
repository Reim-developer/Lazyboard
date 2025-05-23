#include "include/settingButton.hpp"
#include "../language/include/translate.hpp"
#include "../zUtils/include/settings.hpp"
#include "../zUtils/include/config.hpp"
#include "../zUtils/include/zUtils.hpp"
#include "../language/include/language.hpp"
#include "include/zwindow.hpp"
#include <QStringLiteral>
#include <QSettings>
#include <QIcon>
#include "../core/include/setting.hpp"

using zclipboard::core::SettingCore;
using zclipboard::core::SettingCoreParams;
using zclipboard::language::Translate;
using zclipboard::language::TransValue;
using zclipboard::zGui::SettingButton;
using zclipboard::zGui::SettingWidget;

void SettingButton::addSettingButton(QWidget *window, QGridLayout *layout) {
    settingButton = new QPushButton(window);
    settingCore = new SettingCore();

    connect(settingButton, &QPushButton::clicked, this,
            [this, window]() { showSettingDialog(window); });

    layout->addWidget(settingButton, 0, 3);
}

void SettingButton::showSettingDialog(QWidget *parent) {
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
    const auto TYPE = zUtils::languageTypeCast(LANGUAGE);

    Translate::translatorWidget(dialog, TYPE, dialogValue);

    dialog->setFixedSize(FIXED_WIDTH, FIXED_HEIGHT);
    dialog->setWindowIcon(icon);
    dialog->setLayout(layout);
    addGui(layout, dialog);
    dialog->exec();
}

void SettingButton::addGui(QGridLayout *layout, QDialog *dialog) {
    autoHideCheckBox = new QCheckBox();
    autoNotificatonCheckBox = new QCheckBox();
    QComboBox *languageBox = new QComboBox();
    QLabel *languageDescription = new QLabel();

    const int LANGUAGE = settings->value(LANGUAGE_SETTING).toInt();
    const auto TYPE = zUtils::languageTypeCast(LANGUAGE);

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

    struct SettingWidget settingWidget {
        .dialog = dialog,
        .settings = settings,
        .languageDescription = languageDescription,
        .comboBox = languageBox
    };

    // clang-format on

    autoHideCheckBox->setChecked(isHide);
    autoNotificatonCheckBox->setChecked(isNotification);

    addSettingAction(settingWidget);
    Translate::translatorWidget(autoHideCheckBox, TYPE, minimizeValue);
    Translate::translatorWidget(autoNotificatonCheckBox, TYPE, notifiValue);

    layout->addWidget(autoHideCheckBox, 0, 0);
    layout->addWidget(autoNotificatonCheckBox, 1, 0);
    layout->addWidget(languageDescription, 2, 1);
    layout->addWidget(languageBox, 2, 0);
}

void SettingButton::addSettingAction(const SettingWidget &params) {
    // clang-format off
    struct SettingWidget languageSetting {
        .dialog = params.dialog,
        .settings = settings,
        .languageDescription = params.languageDescription,
        .comboBox = params.comboBox
    };

    struct SettingCoreParams notifitionSetting {
        .settings = settings,
        .checkBox = autoNotificatonCheckBox,
    };

    struct SettingCoreParams hideSetting {
        .settings = settings,
        .checkBox = autoHideCheckBox,
    };

    struct SettingCoreParams settingLanguageParams {
        .dialog = params.dialog,
        .settings = settings,
        .languageDescription = params.languageDescription,
        .comboBox = params.comboBox,
        .autoHideCheckBox = autoHideCheckBox,
        .autoNotificatonCheckBox = autoNotificatonCheckBox
    };
    // clang-format on

    settingCore->addLanguageSetting(settingLanguageParams);
    settingCore->addHideSetting(hideSetting);
    settingCore->addNotificationSetting(notifitionSetting);
}

QPushButton *SettingButton::getSettingButton() {
    return settingButton;
}