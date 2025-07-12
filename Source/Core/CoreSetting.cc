#include "Include/CoreSetting.hpp"
#include "../GUI/Include/LanguageManager.hpp"
#include "../GUI/Include/ThemeManager.hpp"
#include "../Language/Include/Translate.hpp"
#include "../Utils/Include/Settings.hpp"
#include "../Language/Include/Language.hpp"
#include "Include/Enum.hpp"
#include "../GUI/Include/InputPasswordDialog.hpp"

using ZClipboard::Core::SettingCore;
using ZClipboard::Language::Translate;
using ZClipboard::GUI::InputPasswordDialog;
using ZClipboard::GUI::LanguageManager;
using ZClipboard::GUI::ThemeManager;

void SettingCore::addHideSetting(const SettingCoreParams &params) {
    const auto function = [this, settings = params.settings](bool isChecked) {
        settings->setValue(AUTO_HIDE_SETTING, isChecked);
    };

    connect(params.checkBox, &QCheckBox::toggled, function);
}

void SettingCore::addNotificationSetting(const SettingCoreParams &params) {
    const auto function = [this, settings = params.settings](bool isChecked) {
        settings->setValue(AUTO_NOTIFICATION_SETTING, isChecked);
    };

    connect(params.checkBox, &QCheckBox::toggled, function);
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
    const auto function = [params](int index) {
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
        const auto SYSTEM_MODE_SECTION_TEXT = TYPE ? SYSTEM_THEME_SECTION_VI : SYSTEM_THEME_SECTION_EN;
        // clang-format on

        params.languageDescription->setText(LABEL_LANGUAGE_DESCRIPTION);
        params.autoHideCheckBox->setText(HIDE_CHECKBOX_TEXT);
        params.autoNotificatonCheckBox->setText(NOTIFICATON_CHECKBOX_TEXT);
        params.dialog->setWindowTitle(DIALOG_TITLE);

        params.themeBox->clear();
        params.themeDescription->setText(LABEL_THEME_DESCRIPTION);
        params.themeBox->addItem(SYSTEM_MODE_SECTION_TEXT);
        params.themeBox->addItem(DARK_MODE_SECTION_TEXT);
        params.themeBox->addItem(LIGHT_MODE_SECTION_TEXT);
    };

    connect(params.languageBox, &QComboBox::currentIndexChanged, this, function);
}

void SettingCore::onThemeSettingChanged(const SettingCoreParams &params) {
    const auto function = [themeBox = params.themeBox,
                           settings = params.settings](const int BOX_INDEX) {
        const int SELECTED_THEME = themeBox->itemData(BOX_INDEX).toInt();
        settings->setValue(THEME_SETTING, SELECTED_THEME);

        ThemeManager::instance().setTheme(SELECTED_THEME);
    };

    connect(params.themeBox, &QComboBox::currentIndexChanged, this, function);
}

void SettingCore::addThemeSetting(const SettingCoreParams &params) {
    const auto LANGUAGE_TYPE = params.settings->value(LANGUAGE_SETTING).toInt();

    /// Language display translator implement.
    // clang-format off
    const auto DARK_MODE_SECTION_TEXT = LANGUAGE_TYPE ? DARK_THEME_SECTION_VI : DARK_THEME_SECTION_EN;
    const auto LIGHT_MODE_SECTION_TEXT = LANGUAGE_TYPE ? LIGHT_THEME_SECTION_VI : LIGHT_THEME_SECTION_EN;
    const auto SYSTEM_MODE_SECTION_TEXT = LANGUAGE_TYPE ? SYSTEM_THEME_SECTION_VI : SYSTEM_THEME_SECTION_EN;
    const auto LABEL_THEME_DESCRIPTION = LANGUAGE_TYPE ? THEME_DESCRIPTION_VI : THEME_DESCRIPTION_EN;
    // clang-format on

    const auto SYSTEM_THEME = static_cast<int>(Theme::SYSTEM);
    const auto DARK_THEME = static_cast<int>(Theme::DARK);
    const auto LIGHT_THEME = static_cast<int>(Theme::LIGHT);

    params.themeBox->addItem(SYSTEM_MODE_SECTION_TEXT, SYSTEM_THEME);
    params.themeBox->addItem(DARK_MODE_SECTION_TEXT, DARK_THEME);
    params.themeBox->addItem(LIGHT_MODE_SECTION_TEXT, LIGHT_THEME);
    params.themeDescription->setText(LABEL_THEME_DESCRIPTION);

    // clang-format off
    const int CURRENT_THEME = params.settings->value(
          THEME_SETTING, static_cast<int>(Theme::SYSTEM)).toInt();
    // clang-format on

    for (int index = 0; index < params.themeBox->count(); ++index) {
        if (params.themeBox->itemData(index).toInt() == CURRENT_THEME) {
            params.themeBox->setCurrentIndex(index);
            break;
        }
    }
}

void SettingCore::onChangePassword(QPushButton *setPasswordButton, QDialog *parent) {
    const auto function = [parent] {
        InputPasswordDialog *guiDialog = new InputPasswordDialog();

        guiDialog->showInputPassword(parent);
    };

    connect(setPasswordButton, &QPushButton::clicked, this, function);
}