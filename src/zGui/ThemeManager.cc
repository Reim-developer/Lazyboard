#include "include/ThemeManager.hpp"
#include "../zUtils/include/config.hpp"
#include "../zUtils/include/settings.hpp"

using zclipboard::zGui::ThemeManager;

ThemeManager::ThemeManager(QObject *parent) : QObject(parent) {
    settings = new QSettings(AUTHOR_NAME, APP_NAME, this);
}

ThemeManager &ThemeManager::instance() {
    static ThemeManager instance;
    return instance;
}

void ThemeManager::setTheme(const int THEME) {
    settings->setValue(THEME_SETTING, THEME);
    emit themeChanged(THEME);
}
