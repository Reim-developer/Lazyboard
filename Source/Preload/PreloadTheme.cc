#include "Include/PreloadTheme.hpp"
#include <QApplication>
#include <QStyleFactory>
#include <QSettings>
#include <QPalette>
#include <QColor>
#include <QStyle>
#include "../Utils/Include/Utils.hpp"
#include "../Utils/Include/Settings.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Core/Include/Enum.hpp"
#include "../GUI/Include/ThemeManager.hpp"

using ZClipboard::Core::Theme;
using ZClipboard::Preload::PreloadTheme;
using ZClipboard::GUI::ThemeManager;
using ZClipboard::AppUtils::Utils;

void PreloadTheme::SetupDefaultTheme() {
    QApplication::setPalette(QPalette());

    switch (Utils::hasPlatform()) {
        case Platform::LINUX:
            QApplication::setStyle(QStyleFactory::create(LINUX_DEFAULT_THEME));
            break;

        case Platform::MACOS:
            QApplication::setStyle(QStyleFactory::create(MACOS_DEFAULT_THEME));
            break;

        case Platform::WINDOWS:
            QApplication::setStyle(QStyleFactory::create(WINDOWS_DEFAULT_THEME));
            break;

        case Platform::UNKNOWN:
            break;
    }
}

void PreloadTheme::SetupLightTheme(QApplication &application) {
    QPalette palette;

    /*
    * Background color.
    */
    palette.setColor(QPalette::Button, LIGHT_BG_COLOR);
    palette.setColor(QPalette::Window, LIGHT_BG_COLOR);
    palette.setColor(QPalette::Base, LIGHT_BG_COLOR);

    /*
    * Foreground color.
    */
    palette.setColor(QPalette::ButtonText, LIGHT_FG_COLOR);
    palette.setColor(QPalette::Text, LIGHT_FG_COLOR);
    palette.setColor(QPalette::WindowText, LIGHT_FG_COLOR);

    application.setPalette(palette);
}

void PreloadTheme::SetupDarkTheme(QApplication &application) {
    QPalette palette;

    /*
    * Background color.
    */
    palette.setColor(QPalette::Button, DARK_BG_COLOR);
    palette.setColor(QPalette::Window, DARK_BG_COLOR);
    palette.setColor(QPalette::Base, DARK_BG_COLOR);

    /*
    * Foreground color.
    */
    palette.setColor(QPalette::ButtonText, DARK_FG_COLOR);
    palette.setColor(QPalette::Text, DARK_FG_COLOR);
    palette.setColor(QPalette::WindowText, DARK_FG_COLOR);

    application.setPalette(palette);
}

void PreloadTheme::LoadSettingTheme(QApplication &application) {
    QSettings settings(AUTHOR_NAME, APP_NAME);
    const auto SETTING_THEME = settings.value(THEME_SETTING).toInt();

    switch (SETTING_THEME) {
        case THEME_DARK:
            SetupDarkTheme(application);
            break;

        case THEME_LIGHT:
            SetupLightTheme(application);
            break;
    }
}

bool PreloadTheme::LoadDefaultTheme() {
    if (!Utils::hasSetting(THEME_SETTING)) {
        SetupDefaultTheme();
        const auto DEFAULT_THEME = static_cast<int>(Theme::SYSTEM);

        QSettings settings(AUTHOR_NAME, APP_NAME);
        settings.setValue(THEME_SETTING, DEFAULT_THEME);

        return true;
    }

    return false;
}

void PreloadTheme::ReloadTheme(const int THEME) {
    const auto APPLICATION = static_cast<QApplication *>(QCoreApplication::instance());
    
    QApplication::setPalette(QPalette());
    switch (THEME) {
        case THEME_SYSTEM:
            SetupDefaultTheme();
            break;

        case THEME_DARK:
            SetupDarkTheme(*APPLICATION);
            break;

        case THEME_LIGHT:
            SetupLightTheme(*APPLICATION);
            break;
    }
}

void PreloadTheme::OnSettingThemeChanged(QApplication &application) {
    connect(&ThemeManager::instance(), &ThemeManager::OnThemeChanged, this, &PreloadTheme::ReloadTheme);
}
