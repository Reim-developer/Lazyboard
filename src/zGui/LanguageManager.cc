#include "include/LanguageManager.hpp"
#include "../zUtils/include/config.hpp"
#include "../zUtils/include/settings.hpp"

using zclipboard::zGui::LanguageManager;

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
