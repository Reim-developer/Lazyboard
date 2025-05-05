#include "include/zwindow.hpp"
#include "include/ztable.hpp"
#include "include/zSearchPanel.hpp"
using zclipboard::zGui::SearchArea;
using zclipboard::zGui::ZTable;
using zclipboard::zGui::ZWindow;

ZWindow::ZWindow(QWidget *zWindow) : QMainWindow(zWindow) {
    zIcon = QIcon(":/assets/assets/icon.png");

    zCentralWidget = new QWidget(zWindow);
    zLayout = new QGridLayout(zCentralWidget);

    setCentralWidget(zCentralWidget);
    setWindowTitle("zClipboard");

    resize(800, 600);
    setWindowIcon(zIcon);

    setupGui();
}

void ZWindow::setupGui() {
    ztable = new ZTable();
    zSearchArea = new SearchArea();

    ztable->addZtable(this, zLayout);
    auto zModel = ztable->getZModel();
    zSearchArea->addSearchPanel(this, zLayout, zModel);
}