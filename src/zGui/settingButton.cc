#include "include/settingButton.hpp"
#include "../zUtils/include/settings.hpp"
#include <QStringLiteral>
#include <QSettings>
#include <QIcon>

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
    constexpr int FIXED_WIDTH = 400;
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

    bool isHide = settings->value(AUTO_HIDE_SETTING).toBool();
    bool isNotification = settings->value(AUTO_NOTIFICATION_SETTING).toBool();

    autoHideCheckBox->setText(QStringLiteral("Minimize to system tray on window close."));
    autoNotificatonCheckBox->setText(QStringLiteral("Notify me when clipboard changes."));

    autoHideCheckBox->setChecked(isHide);
    autoNotificatonCheckBox->setChecked(isNotification);
    addHideSetting(autoHideCheckBox, settings);
    addNotificationSetting(autoNotificatonCheckBox, settings);

    layout->addWidget(autoHideCheckBox, 0, 0);
    layout->addWidget(autoNotificatonCheckBox, 1, 0);
}

void SettingButton::addHideSetting(QCheckBox *autoHideCheckBox, QSettings *settings) {
    connect(autoHideCheckBox, &QCheckBox::toggled,
            [this, settings](bool isChecked) { settings->setValue(AUTO_HIDE_SETTING, isChecked); });
}

void SettingButton::addNotificationSetting(QCheckBox *autoNotificatonCheckBox,
                                           QSettings *settings) {
    connect(autoNotificatonCheckBox, &QCheckBox::toggled, [this, settings](bool isChecked) {
        settings->setValue(AUTO_NOTIFICATION_SETTING, isChecked);
    });
}