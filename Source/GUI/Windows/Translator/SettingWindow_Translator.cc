#include "Include/SettingWindow_Translator.hpp"
#include "../../../Language/Include/Language.hpp"

using ZClipboard::GUI::Windows::Translator::SettingWindowTranslator;
using ZClipboard::Lib_Memory::MakePtr;

using Self = SettingWindowTranslator;

#if defined (Z_DEBUG)

#endif 

void Self::VietNameseTranslator(Window *window, Components *components) {
    constexpr auto TITLE = SETTING_DIALOG_VI;
    

    window->setWindowTitle(TITLE);
}

void Self::EnglishTranslator(Window *window, Components *components) {
    const auto TITLE = SETTING_DIALOG_EN;

    window->setWindowTitle(TITLE);
}

void Self::LoadTranslator(Window *window, Components *components) {
    if(!settings) {
        settings = MakePtr<Settings>();


    }

}