#include "include/setting.hpp"
#include "../zGui/include/LanguageManager.hpp"
#include "../zUtils/include/settings.hpp"
#include "../language/include/language.hpp"

using zclipboard::core::SettingCore;
using zclipboard::zGui::LanguageManager;

void SettingCore::addHideSetting(const SettingCoreParams &params) {
    connect(params.checkBox, &QCheckBox::toggled,
            [this, settings = params.settings](bool isChecked) {
                settings->setValue(AUTO_HIDE_SETTING, isChecked);
            });
}

void SettingCore::addNotificationSetting(const SettingCoreParams &params) {
    connect(params.checkBox, &QCheckBox::toggled,
            [this, settings = params.settings](bool isChecked) {
                settings->setValue(AUTO_NOTIFICATION_SETTING, isChecked);
            });
}

void SettingCore::addLanguageSetting(const SettingCoreParams &params) {
    connect(params.comboBox, &QComboBox::currentIndexChanged, this, [params](int index) {
        int selectedLanguage = params.comboBox->itemData(index).toInt();
        params.settings->setValue(LANGUAGE_SETTING, selectedLanguage);

        LanguageManager::instance().setLanguage(selectedLanguage);

        const int TYPE = params.settings->value(LANGUAGE_SETTING).toInt();

        const auto LABEL_TITLE = TYPE ? LABEL_DESCRIPTION_VI : LABEL_DESCRIPTION_EN;
        const auto NOTIFICATON_CHECKBOX_TEXT =
            TYPE ? NOTIFICATION_CHECKBOX_VI : NOTIFICATION_CHECKBOX_EN;
        const auto HIDE_CHECKBOX_TEXT = TYPE ? MINIMIZE_CHECKBOX_VI : MINIMIZE_CHECKBOX_EN;
        const auto DIALOG_TITLE = TYPE ? SETTING_DIALOG_VI : SETTING_DIALOG_EN;

        params.languageDescription->setText(LABEL_TITLE);
        params.autoHideCheckBox->setText(HIDE_CHECKBOX_TEXT);
        params.autoNotificatonCheckBox->setText(NOTIFICATON_CHECKBOX_TEXT);
        params.dialog->setWindowTitle(DIALOG_TITLE);
    });
}