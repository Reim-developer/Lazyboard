#include "Include/LanguageManager.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Utils/Include/Settings.hpp"

using ZClipboard::GUI::LanguageManager;

LanguageManager::LanguageManager(QObject *parent) : QObject(parent) {
    settings = new QSettings(AUTHOR_NAME, APP_NAME, this);
}

LanguageManager &LanguageManager::instance() {
    static LanguageManager instance;
    return instance;
}

void LanguageManager::setLanguage(int language) {
    settings->setValue(LANGUAGE_SETTING, language);
    
    emit languageChanged(language);
}
