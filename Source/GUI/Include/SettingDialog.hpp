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
#include <QMainWindow>
#include "../../Core/Include/CoreSetting.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"

using ZClipboard::Core::SettingCore;

GUI_NAMESPACE

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
        void SetupSettingButton(QMainWindow *window, QGridLayout *layout);
        QPushButton *getSettingButton();

    private:
        void showSettingDialog(QMainWindow *parent);
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
    
END_NAMESPACE

#endif  // SETTING_BUTTON_HPP