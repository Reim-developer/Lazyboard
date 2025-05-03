#include "include/zwindow.hpp"
#include "include/ztable.hpp"
using namespace zclipboard::zgui;

ZWindow::ZWindow(QWidget *zWindow) : QMainWindow(zWindow) {
    zIcon = QIcon(":/assets/assets/icon.png");
    
    zCentralWidget = new QWidget(zWindow);
    zLayout = new QGridLayout(zCentralWidget);

    setCentralWidget(zCentralWidget);
    setWindowTitle("zClipboard");

    setMinimumSize(600, 600);
    setWindowIcon(zIcon);

    setupGui();
}

void ZWindow::setupGui() {
    ztable = new ZTable();
    ztable->addZtable(this, zLayout);
}