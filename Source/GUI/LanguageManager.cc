#include "Include/LanguageManager.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Utils/Include/Settings.hpp"
#include "../Utils/Include/Meta_Macro.hpp"
#include <qtmetamacros.h>

using ZClipboard::GUI::LanguageManager;

LanguageManager::LanguageManager() {
    #if !defined (_WIN32)

        MAKE_SMART_PTR(QSettings, settings, (AUTHOR_NAME, APP_NAME));

    #else
        settings = MakePtr<QSettings>(AUTHOR_NAME, APP_NAME);

    #endif 
}

LanguageManager &LanguageManager::GetLanguageManager() {
    static LanguageManager languageManager;
    
    return languageManager;
}

void LanguageManager::SetLanguage(int language) {
    settings->setValue(LANGUAGE_SETTING, language);
    
    emit OnLanguageChanged(language);
}
