#include "include/settingButton.hpp"
#include "../language/include/translate.hpp"
#include "../zUtils/include/settings.hpp"
#include <QStringLiteral>
#include <QSettings>
#include <QIcon>

using zclipboard::language::Translate;
using zclipboard::zGui::SettingButton;

void SettingButton::addSettingButton(QWidget *window, QGridLayout *layout) {
    settingButton = new QPushButton(window);

    settingButton->setText(QStringLiteral("Settings"));

    connect(settingButton, &QPushButton::clicked, this,
            [this, window]() { showSettingDialog(window); });

    layout->addWidget(settingButton, 0, 3);
}

void SettingButton::showSettingDialog(QWidget *parent) {
    QDialog *dialog = new QDialog(parent);
    layout = new QGridLayout(dialog);

    QIcon icon = QIcon(QStringLiteral(":/assets/assets/icon.png"));
    constexpr int FIXED_WIDTH = 600;
    constexpr int FIXED_HEIGHT = 400;

    dialog->setWindowTitle(QStringLiteral("ZClipboard - Setting"));
    dialog->setFixedSize(FIXED_WIDTH, FIXED_HEIGHT);
    dialog->setWindowIcon(icon);
    dialog->setLayout(layout);
    addGui(layout);
    dialog->exec();
}

void SettingButton::addGui(QGridLayout *layout) {
    QSettings *settings = new QSettings();
    autoHideCheckBox = new QCheckBox();
    autoNotificatonCheckBox = new QCheckBox();
    QComboBox *languageBox = new QComboBox();
    QLabel *languageDescription = new QLabel();

    bool isHide = settings->value(AUTO_HIDE_SETTING).toBool();
    bool isNotification = settings->value(AUTO_NOTIFICATION_SETTING).toBool();

    autoHideCheckBox->setText(QStringLiteral("Minimize to system tray on window close."));
    autoNotificatonCheckBox->setText(QStringLiteral("Notify me when clipboard changes."));

    autoHideCheckBox->setChecked(isHide);
    autoNotificatonCheckBox->setChecked(isNotification);

    addHideSetting({.checkbox = autoHideCheckBox, .settings = settings});
    addNotificationSetting({.checkbox = autoNotificatonCheckBox, .settings = settings});
    addLanguageSetting({.settings = settings,
                        .languageDescription = languageDescription,
                        .comboBox = languageBox});

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
    settingWidget.languageDescription->setText(QStringLiteral("Language Display"));
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

    connect(settingWidget.comboBox, &QComboBox::currentIndexChanged, this,
            [settings = settingWidget.settings, comboBox = settingWidget.comboBox](int index) {
                int selectedLanguage = comboBox->itemData(index).toInt();
                settings->setValue(LANGUAGE_SETTING, selectedLanguage);
                settings->sync();
            });
}