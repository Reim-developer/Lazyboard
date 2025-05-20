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
#include "include/LanguageManager.hpp"

using zclipboard::language::Translate;
using zclipboard::language::TransValue;
using zclipboard::zGui::SettingButton;
using zclipboard::zGui::SettingWidget;

void SettingButton::addSettingButton(QWidget *window, QGridLayout *layout) {
    settingButton = new QPushButton(window);

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

    autoHideCheckBox->setChecked(isHide);
    autoNotificatonCheckBox->setChecked(isNotification);

    // clang-format off
    TransValue minimizeValue {
        .LANGUAGE_EN = MINIMIZE_CHECKBOX_EN,
        .LANGUAGE_VI = MINIMIZE_CHECKBOX_VI
    };

    TransValue notifiValue {
        .LANGUAGE_EN = NOTIFICATION_CHECKBOX_EN,
        .LANGUAGE_VI = NOTIFICATION_CHECKBOX_VI
    };
    // clang-format on

    Translate::translatorWidget(autoHideCheckBox, TYPE, minimizeValue);
    Translate::translatorWidget(autoNotificatonCheckBox, TYPE, notifiValue);

    // clang-format off
    struct SettingWidget languageSetting {
        .dialog = dialog,
        .settings = settings,
        .languageDescription = languageDescription,
        .comboBox = languageBox
    };

    struct SettingWidget notifitionSetting {
        .checkbox = autoNotificatonCheckBox,
        .settings = settings
    };

    struct SettingWidget hideSetting {
        .checkbox = autoHideCheckBox,
        .settings = settings
    };
    // clang-format on

    addHideSetting(hideSetting);
    addNotificationSetting(notifitionSetting);
    addLanguageSetting(languageSetting);

    layout->addWidget(autoHideCheckBox, 0, 0);
    layout->addWidget(autoNotificatonCheckBox, 1, 0);
    layout->addWidget(languageDescription, 2, 1);
    layout->addWidget(languageBox, 2, 0);
}

void SettingButton::addHideSetting(const SettingWidget &settingWidget) {
    connect(settingWidget.checkbox, &QCheckBox::toggled,
            [this, settings = settingWidget.settings](bool isChecked) {
                settings->setValue(AUTO_HIDE_SETTING, isChecked);
            });
}

void SettingButton::addNotificationSetting(const SettingWidget &settingWidget) {
    connect(settingWidget.checkbox, &QCheckBox::toggled,
            [this, settings = settingWidget.settings](bool isChecked) {
                settings->setValue(AUTO_NOTIFICATION_SETTING, isChecked);
            });
}

void SettingButton::addLanguageSetting(const SettingWidget &settingWidget) {
    const int TYPE = settings->value(LANGUAGE_SETTING).toInt();

    const auto LABEL_TITLE = TYPE ? LABEL_DESCRIPTION_VI : LABEL_DESCRIPTION_EN;
    settingWidget.languageDescription->setText(LABEL_TITLE);

    settingWidget.comboBox->addItem(QStringLiteral("English"),
                                    static_cast<int>(Translate::ENGLISH));
    settingWidget.comboBox->addItem(QStringLiteral("VietNamese"),
                                    static_cast<int>(Translate::VIETNAMESE));

    int currentLanguage =
        settingWidget.settings->value(LANGUAGE_SETTING, static_cast<int>(Translate::ENGLISH))
            .toInt();

    for (int index = 0; index < settingWidget.comboBox->count(); ++index) {
        if (settingWidget.comboBox->itemData(index).toInt() == currentLanguage) {
            settingWidget.comboBox->setCurrentIndex(index);
            break;
        }
    }
    // clang-format off
    connect(settingWidget.comboBox, &QComboBox::currentIndexChanged, this, 
        [this, settings = settingWidget.settings, 
                    comboBox = settingWidget.comboBox,
                    label = settingWidget.languageDescription, 
                    dialog = settingWidget.dialog]
                    (int index) {

        int selectedLanguage = comboBox->itemData(index).toInt();
        settings->setValue(LANGUAGE_SETTING, selectedLanguage);

        LanguageManager::instance().setLanguage(selectedLanguage);

        const int TYPE = settings->value(LANGUAGE_SETTING).toInt();
    
        const auto LABEL_TITLE = TYPE ? LABEL_DESCRIPTION_VI : LABEL_DESCRIPTION_EN;
        const auto NOTIFICATON_CHECKBOX_TEXT = TYPE ? NOTIFICATION_CHECKBOX_VI : NOTIFICATION_CHECKBOX_EN;
        const auto HIDE_CHECKBOX_TEXT = TYPE ? MINIMIZE_CHECKBOX_VI : MINIMIZE_CHECKBOX_EN;
        const auto DIALOG_TITLE = TYPE ? SETTING_DIALOG_VI : SETTING_DIALOG_EN;
                
        label->setText(LABEL_TITLE);
        autoHideCheckBox->setText(HIDE_CHECKBOX_TEXT);
        autoNotificatonCheckBox->setText(NOTIFICATON_CHECKBOX_TEXT);
        dialog->setWindowTitle(DIALOG_TITLE);
    });
    // clang-format on
}

QPushButton *SettingButton::getSettingButton() {
    return settingButton;
}