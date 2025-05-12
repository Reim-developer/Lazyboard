#include "include/zwindow.hpp"
#include "include/clearButton.hpp"
#include "include/getButton.hpp"
#include "include/ztable.hpp"
#include "include/zSearchPanel.hpp"
#include <QStringLiteral>

using zclipboard::zGui::GetButton;
using zclipboard::zGui::SearchArea;
using zclipboard::zGui::ZTable;
using zclipboard::zGui::ZWindow;

ZWindow::ZWindow(QWidget *zWindow) : QMainWindow(zWindow) {
    zIcon = QIcon(QStringLiteral(":/assets/assets/icon.png"));

    zCentralWidget = new QWidget(zWindow);
    zLayout = new QGridLayout(zCentralWidget);

    setCentralWidget(zCentralWidget);
    setWindowTitle(QStringLiteral("zClipboard"));

    resize(Z_WINDOW_WIDTH, Z_WINDOW_HEIGHT);
    setWindowIcon(zIcon);
    setupGui();
}

void ZWindow::setupGui() {
    ztable = new ZTable();
    zSearchArea = new SearchArea();
    clearButton = new ClearButton();
    getButton = new GetButton();

    ztable->addZtable(this, zLayout);
    zSearchArea->addSearchPanel(this, zLayout, ztable);
    clearButton->addClearButton(zLayout, ztable);
    getButton->addGetButton(this, zLayout);
}