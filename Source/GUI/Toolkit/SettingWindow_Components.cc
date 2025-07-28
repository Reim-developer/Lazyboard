#include "Include/SettingWindow_Components.hpp"
#include "../../Utils/Include/Utils.hpp"

using ZClipboard::GUI::Toolkit::SettingWindowComponentsManager;
using ZClipboard::AppUtils::Utils;

using Self = SettingWindowComponentsManager;

using Button = QPushButton;
using Label = QLabel;

using ComboBox = QComboBox;
using CheckBox = QCheckBox;

Button *Self::GetSetPasswordButton() {
    if(!setPasswordButton) {
        Utils::MakeSmartPtr<Button>(setPasswordButton);
    }

    return setPasswordButton.get();
}

Label *Self::GetLanguageDescription() {
    if(!languageDescription) {
        Utils::MakeSmartPtr<Label>(languageDescription);
    }

    return languageDescription.get();
}

Label *Self::GetThemeDescription() {
    if(!themeDescription) {
        Utils::MakeSmartPtr<Label>(themeDescription);
    }

    return themeDescription.get();
}

ComboBox *Self::GetLanguageListBox() {
    if(!languageBox) {
        Utils::MakeSmartPtr<ComboBox>(languageBox);
    }

    return languageBox.get();
}

ComboBox *Self::GetThemeListBox() {
    if(!themeBox) {
        Utils::MakeSmartPtr<ComboBox>(themeBox);
    }

    return themeBox.get();
}

CheckBox *Self::GetHideSettingCheckBox() {
    if(!autoHideCheckBox) {
        Utils::MakeSmartPtr<CheckBox>(autoHideCheckBox);
    }

    return autoHideCheckBox.get();
}

CheckBox *Self::GetNotificationCheckBox() {
    if(!autoNotificatonCheckBox) {
        Utils::MakeSmartPtr<CheckBox>(autoNotificatonCheckBox);
    }

    return autoNotificatonCheckBox.get();
}