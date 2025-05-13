#include "include/settingButton.hpp"
#include <QStringLiteral>
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
    QIcon icon = QIcon(QStringLiteral(":/assets/assets/icon.png"));
    constexpr int FIXED_WIDTH = 400;
    constexpr int FIXED_HEIGHT = 400;

    dialog->setWindowTitle(QStringLiteral("ZClipboard - Setting"));
    dialog->setFixedSize(FIXED_WIDTH, FIXED_HEIGHT);
    dialog->setWindowIcon(icon);
    dialog->exec();
}