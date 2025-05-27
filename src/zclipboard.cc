#include "zGui/include/zwindow.hpp"
#include "preload/include/theme.hpp"
#include <QApplication>
#include <memory>

using std::make_unique;
using std::unique_ptr;
using zclipboard::preload::Application;
using zclipboard::zGui::ZWindow;

int main(int argc, char *argv[]) {
    unique_ptr<Application> zClipboard = make_unique<Application>();
    const bool IS_DEFAULT_THEME = zClipboard->loadDefaultTheme();

    QApplication application(argc, argv);
    if (!IS_DEFAULT_THEME) {
        zClipboard->loadSettingTheme(application);
    }

    ZWindow zWindow;
    zWindow.show();

    return application.exec();
}