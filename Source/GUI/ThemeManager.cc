#include "Include/ThemeManager.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Utils/Include/Settings.hpp"

using ZClipboard::GUI::ThemeManager;

ThemeManager::ThemeManager(QObject *parent) : QObject(parent) {
    settings = new QSettings(AUTHOR_NAME, APP_NAME, this);
}

ThemeManager &ThemeManager::instance() {
    static ThemeManager instance;
    return instance;
}

void ThemeManager::setTheme(const int THEME) {
    settings->setValue(THEME_SETTING, THEME);
    emit OnThemeChanged(THEME);
}
