#include "zGui/include/zwindow.hpp"
#include <QApplication>

using zclipboard::zGui::ZWindow;

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    
    ZWindow zWindow;
    zWindow.show();
    
    return  application.exec();
}