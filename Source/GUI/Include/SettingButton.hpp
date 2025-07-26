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
#include "../../Lib_Memory/Include/Memory.hpp"
#include "../Toolkit/Include/MainWindow_Components.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../../GUI/Windows/Include/SettingWindow.hpp"
#include "../../Listener/Include/ListenerOpenSettingWindow.hpp"

using ZClipboard::GUI::Toolkit::MainWindowComponentsManager;
using ZClipboard::GUI::Windows::SettingWindowManager;
using ZClipboard::Core::CoreSettingWindow;
using ZClipboard::Listener::ListenerOpenSettingWindow;
using ZClipboard::Lib_Memory::PtrUnique;

GUI_NAMESPACE

    // struct SettingWidget {
    //     QCheckBox *checkbox;
    //     QDialog *dialog;
    //     QSettings *settings;
    //     QLabel *languageDescription;
    //     QGridLayout *layout;
    //     QComboBox *comboBox;
    // };

    class SettingButton : public QObject {
        Q_OBJECT

    private:
        using Window = QMainWindow;
        using Components = MainWindowComponentsManager;
        using Listener = ListenerOpenSettingWindow;
        using Button = QPushButton;

    private:
        void SetupListener(Button *openSettingButton);

    public:
        void SetupSettingButton(Window *window, Components *components);
        // QPushButton *getSettingButton();

    private:
        // void showSettingDialog(QMainWindow *parent);
        // void addGui(QGridLayout *layout, QDialog *dialog);
        // void addSettingCheckboxAction();
        // void addLanguageSectionAction(QDialog *dialog);
        // void addThemeSectionAction();

    private:
        // PtrUnique<QSettings> settings;
        // PtrUnique<QDialog> dialog;
        // PtrUnique<QGridLayout> layout;
        PtrUnique<Listener> listener;
        // QPushButton *setPasswordButton;

        // QLabel *languageDescription;
        // QLabel *themeDescription;

        // QComboBox *languageBox;
        // QComboBox *themeBox;

        // QCheckBox *autoHideCheckBox;
        // QCheckBox *autoNotificatonCheckBox;
    };
    
END_NAMESPACE

#endif  // SETTING_BUTTON_HPP