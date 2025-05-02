#include "gui/include/zwindow.hpp"
#include <QApplication>

using namespace zclipboard::zgui;

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    
    ZWindow zWindow;
    zWindow.show();
    
    return  application.exec();
}