#include "include/setting.hpp"
#include "../zGui/include/LanguageManager.hpp"
#include "../language/include/translate.hpp"
#include "../zUtils/include/settings.hpp"
#include "../language/include/language.hpp"

using zclipboard::core::SettingCore;
using zclipboard::language::Translate;
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
    const int TYPE = params.settings->value(LANGUAGE_SETTING).toInt();
    const auto LABEL_TITLE = TYPE ? LABEL_DESCRIPTION_VI : LABEL_DESCRIPTION_EN;

    params.languageDescription->setText(LABEL_TITLE);

    params.languageBox->addItem(QStringLiteral("English"), static_cast<int>(Translate::ENGLISH));
    params.languageBox->addItem(QStringLiteral("VietNamese"),
                                static_cast<int>(Translate::VIETNAMESE));

    int currentLanguage =
        params.settings->value(LANGUAGE_SETTING, static_cast<int>(Translate::ENGLISH)).toInt();

    for (int index = 0; index < params.languageBox->count(); ++index) {
        if (params.languageBox->itemData(index).toInt() == currentLanguage) {
            params.languageBox->setCurrentIndex(index);
            break;
        }
    }
}

void SettingCore::onLanguageSettingChanged(const SettingCoreParams &params) {
    connect(params.languageBox, &QComboBox::currentIndexChanged, this, [params](int index) {
        int selectedLanguage = params.languageBox->itemData(index).toInt();
        params.settings->setValue(LANGUAGE_SETTING, selectedLanguage);

        LanguageManager::instance().setLanguage(selectedLanguage);

        const int TYPE = params.settings->value(LANGUAGE_SETTING).toInt();

        // clang-format off
        /*
        * Implement language translator for display.
        */
        const auto LABEL_LANGUAGE_DESCRIPTION = TYPE ? LABEL_DESCRIPTION_VI : LABEL_DESCRIPTION_EN;
        const auto LABEL_THEME_DESCRIPTION = TYPE ? THEME_DESCRIPTION_VI : THEME_DESCRIPTION_EN;
        const auto NOTIFICATON_CHECKBOX_TEXT = TYPE ? NOTIFICATION_CHECKBOX_VI : NOTIFICATION_CHECKBOX_EN;
        const auto HIDE_CHECKBOX_TEXT = TYPE ? MINIMIZE_CHECKBOX_VI : MINIMIZE_CHECKBOX_EN;
        const auto DIALOG_TITLE = TYPE ? SETTING_DIALOG_VI : SETTING_DIALOG_EN;
        const auto DARK_MODE_SECTION_TEXT = TYPE ? DARK_THEME_SECTION_VI : DARK_THEME_SECTION_EN;
        const auto LIGHT_MODE_SECTION_TEXT = TYPE ? LIGHT_THEME_SECTION_VI : LIGHT_THEME_SECTION_EN;
        // clang-format on

        params.languageDescription->setText(LABEL_LANGUAGE_DESCRIPTION);
        params.autoHideCheckBox->setText(HIDE_CHECKBOX_TEXT);
        params.autoNotificatonCheckBox->setText(NOTIFICATON_CHECKBOX_TEXT);
        params.dialog->setWindowTitle(DIALOG_TITLE);

        params.themeBox->clear();
        params.themeDescription->setText(LABEL_THEME_DESCRIPTION);
        params.themeBox->addItem(DARK_MODE_SECTION_TEXT);
        params.themeBox->addItem(LIGHT_MODE_SECTION_TEXT);
    });
}

void SettingCore::addThemeSetting(const SettingCoreParams &params) {
    const auto TYPE = params.settings->value(LANGUAGE_SETTING).toInt();

    /// Language display translator implement.
    const auto DARK_MODE_SECTION_TEXT = TYPE ? DARK_THEME_SECTION_VI : DARK_THEME_SECTION_EN;
    const auto LIGHT_MODE_SECTION_TEXT = TYPE ? LIGHT_THEME_SECTION_VI : LIGHT_THEME_SECTION_EN;
    const auto LABEL_THEME_DESCRIPTION = TYPE ? THEME_DESCRIPTION_VI : THEME_DESCRIPTION_EN;

    params.themeBox->addItem(DARK_MODE_SECTION_TEXT);
    params.themeBox->addItem(LIGHT_MODE_SECTION_TEXT);
    params.themeDescription->setText(LABEL_THEME_DESCRIPTION);
}