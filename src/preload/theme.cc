#include "include/theme.hpp"
#include "../zUtils/include/zUtils.hpp"

using zclipboard::preload::Application;

void Application::loadTheme() {
    if (!zUtils::hasDefaultSystemTheme()) {
        zUtils::setDefaultTheme();
    }
}
