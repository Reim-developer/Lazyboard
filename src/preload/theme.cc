#include "include/theme.hpp"
#include <QApplication>
#include <QStyleFactory>
#include "../zUtils/include/zUtils.hpp"
#include "../zUtils/include/settings.hpp"

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

void Application::loadTheme() {
    if (!zUtils::hasSetting(THEME_SETTING)) {
        setDefaultTheme();
    }
}
