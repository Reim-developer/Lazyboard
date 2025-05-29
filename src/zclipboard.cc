#include "zGui/include/zwindow.hpp"
#include "preload/include/theme.hpp"
#include <QApplication>
#include <memory>

using std::make_unique;
using std::unique_ptr;
using zclipboard::preload::Application;
using zclipboard::zGui::ZWindow;

int main(int argc, char *argv[]) {
    unique_ptr<Application> preloadApplication = make_unique<Application>();
    const bool IS_DEFAULT_THEME = preloadApplication->loadDefaultTheme();

    QApplication application(argc, argv);
    if (!IS_DEFAULT_THEME) {
        preloadApplication->loadSettingTheme(application);
    }

    preloadApplication->onSettingThemeChanged(application);

    ZWindow zWindow;
    zWindow.show();

    return application.exec();
}