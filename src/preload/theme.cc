#include "include/theme.hpp"
#include <QApplication>
#include <QStyleFactory>
#include <QSettings>
#include <QPalette>
#include <QColor>
#include "../zUtils/include/zUtils.hpp"
#include "../zUtils/include/settings.hpp"
#include "../zUtils/include/config.hpp"
#include "../core/include/enum.hpp"

using zclipboard::core::Theme;
using zclipboard::preload::Application;

void Application::setDefaultTheme() {
    switch (zUtils::hasPlatform()) {
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

void Application::setLightTheme(QApplication &application) {
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

    application.setPalette(palette);
}

void Application::setDarkTheme(QApplication &application) {
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

    application.setPalette(palette);
}

void Application::loadSettingTheme(QApplication &application) {
    QSettings settings(AUTHOR_NAME, APP_NAME);
    const auto SETTING_THEME = settings.value(THEME_SETTING).toInt();

    switch (SETTING_THEME) {
        case THEME_DARK:
            setDarkTheme(application);
            break;

        case THEME_LIGHT:
            setLightTheme(application);
            break;
    }
}

bool Application::loadDefaultTheme() {
    if (!zUtils::hasSetting(THEME_SETTING)) {
        setDefaultTheme();
        const auto DEFAULT_THEME = static_cast<int>(Theme::SYSTEM);

        QSettings settings(AUTHOR_NAME, APP_NAME);
        settings.setValue(THEME_SETTING, DEFAULT_THEME);

        return true;
    }

    return false;
}
