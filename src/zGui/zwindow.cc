#include "include/zwindow.hpp"
#include "include/clearButton.hpp"
#include "include/getButton.hpp"
#include "include/settingButton.hpp"
#include "include/ztable.hpp"
#include "include/zSearchPanel.hpp"
#include "../zUtils/include/zUtils.hpp"
#include <QStringLiteral>
#include <QApplication>

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
    createTrayIcon();
    setupGui();
}

void ZWindow::createTrayIcon() {
    trayIcon = new QSystemTrayIcon(this);
    trayMenu = new QMenu();

    QAction *showGui = trayMenu->addAction(QStringLiteral("Show ZClipboard"));
    QAction *quitGui = trayMenu->addAction(QStringLiteral("Quit ZClipboard"));
    QAction *hideGui = trayMenu->addAction(QStringLiteral("Hide ZClipboard"));

    addTrayMenuActions(trayIcon);
    connect(showGui, &QAction::triggered, this, &ZWindow::showNormal);
    connect(quitGui, &QAction::triggered, this, &QApplication::quit);
    connect(hideGui, &QAction::triggered, this, &ZWindow::hide);

    trayIcon->setIcon(zIcon);
    trayIcon->setToolTip(QStringLiteral("Manage your clipboard - ZClipboard"));
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}

void ZWindow::addTrayMenuActions(QSystemTrayIcon *trayIcon) {
    connect(trayIcon, &QSystemTrayIcon::activated,
            [this](QSystemTrayIcon::ActivationReason reason) {
                if (reason == QSystemTrayIcon::DoubleClick || reason == QSystemTrayIcon::Trigger) {
                    showNormal();
                    activateWindow();
                }
            });
}

void ZWindow::setupGui() {
    ztable = new ZTable();
    zSearchArea = new SearchArea();
    clearButton = new ClearButton();
    getButton = new GetButton();
    settingButton = new SettingButton();

    ztable->addZtable(this, zLayout);
    zSearchArea->addSearchPanel(this, zLayout, ztable);
    clearButton->addClearButton(zLayout, ztable);
    getButton->addGetButton(this, zLayout);
    settingButton->addSettingButton(this, zLayout);

    zUtils::textClipboardChanges(trayIcon, ztable->getClipboard());
    zUtils::imageClipboardChanges(trayIcon, ztable->getClipboard());
}

void ZWindow::closeEvent(QCloseEvent *event) {
    if (zUtils::getAutoHideSetting()) {
        hide();
        event->ignore();
    } else {
        event->accept();
    }
}