#ifndef SETTING_BUTTON_HPP
#define SETTING_BUTTON_HPP
#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QObject>
#include <QCheckBox>
#include <QGridLayout>
#include <QSettings>
#include <QComboBox>
#include <QLabel>
#include "../../core/include/setting.hpp"

using zclipboard::core::SettingCore;

namespace zclipboard::zGui {

struct SettingWidget {
    QCheckBox *checkbox;
    QDialog *dialog;
    QSettings *settings;
    QLabel *languageDescription;
    QGridLayout *layout;
    QComboBox *comboBox;
};

class SettingButton : public QObject {
    Q_OBJECT

   public:
    void addSettingButton(QWidget *window, QGridLayout *layout);
    QPushButton *getSettingButton();

   private:
    void showSettingDialog(QWidget *parent);
    void addGui(QGridLayout *layout, QDialog *dialog);
    void addSettingCheckboxAction();
    void addLanguageSectionAction(QDialog *dialog);
    void addThemeSectionAction();

   private:
    SettingCore *settingCore;
    QSettings *settings;
    QPushButton *settingButton;
    QGridLayout *layout;

    QPushButton *setPasswordButton;

    QLabel *languageDescription;
    QLabel *themeDescription;

    QComboBox *languageBox;
    QComboBox *themeBox;

    QCheckBox *autoHideCheckBox;
    QCheckBox *autoNotificatonCheckBox;
};
}  // namespace zclipboard::zGui

#endif  // SETTING_BUTTON_HPP