#ifndef SETTING_WINDOW_COMPONENTS_HPP
#define SETTING_WINDOW_COMPONENTS_HPP
#include "../../../Utils/Include/Namespace_Macro.hpp"
#include "../../../Lib_Memory/Include/Memory.hpp"
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>

using ZClipboard::Lib_Memory::PtrUnique;

GUI_TOOLKIT_NAMESPACE

    class SettingWindowComponents {
        private:
            using Button = QPushButton;
            using ComboBox = QComboBox;
            using CheckBox = QCheckBox;
            using Label = QLabel;

        private:
            PtrUnique<QPushButton> setPasswordButton;
            PtrUnique<QLabel> languageDescription;
            PtrUnique<QLabel> themeDescription;

            PtrUnique<QComboBox> languageBox;
            PtrUnique<QComboBox> themeBox;

            PtrUnique<QCheckBox> autoHideCheckBox;
            PtrUnique<QCheckBox> autoNotificatonCheckBox;

        public:
            Button *GetSetPasswordButton();

            Label *GetLanguageDescription();
            Label *GetThemeDescription();

            ComboBox *GetLanguageListBox();
            ComboBox *GetThemeListBox();

            CheckBox *GetHideSettingCheckBox();
            CheckBox *GetNotificationCheckBox();

    };

END_NAMESPACE

#endif // SETTING_WINDOW_COMPONENTS_HPP