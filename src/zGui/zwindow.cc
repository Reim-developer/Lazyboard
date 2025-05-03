#include "include/zwindow.hpp"
#include "include/ztable.hpp"
#include "include/zSearchPanel.hpp"
using zclipboard::zGui::ZTable;
using zclipboard::zGui::ZWindow;
using zclipboard::zGui::SearchArea;

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
    zSearchArea = new SearchArea();

    zSearchArea->addSearchPanel(this, zLayout);
    ztable->addZtable(this, zLayout);
}