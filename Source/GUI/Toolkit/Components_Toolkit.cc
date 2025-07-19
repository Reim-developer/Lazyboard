#include "Include/Components_Toolkit.hpp"

using ZClipboard::GUI::Toolkit::ComponentsToolkit;
using Self = ComponentsToolkit;

QTableView *Self::GetTableView() {
    if(!ClipboardTableView) {
        Utils::MakeSmartPtr<QTableView>(ClipboardTableView);
    }

    return ClipboardTableView.get();
}

TableModel *Self::GetTableModel() {
    if(!ModelTable) {
        Utils::MakeSmartPtr<TableModel>(ModelTable);
    }

    return ModelTable.get();
}

QLineEdit *Self::GetSearchArea() {
    if(!SearchArea) {
        Utils::MakeSmartPtr<QLineEdit>(SearchArea);
    }

    return SearchArea.get();
}

QPushButton *Self::GetClearButton() {
    if(!ClearButton) {
        Utils::MakeSmartPtr<QPushButton>(ClearButton);
    }

    return ClearButton.get();
}

QPushButton *Self::GetDisconnectButton() {
    if(!DisconnectButton) {
        Utils::MakeSmartPtr<QPushButton>(DisconnectButton);
    }

    return DisconnectButton.get();
}

QPushButton *Self::GetConnectButton() {
    if(!ConnectButton) {
        Utils::MakeSmartPtr<QPushButton>(ConnectButton);
    }

    return ConnectButton.get();
}

QSystemTrayIcon *Self::GetSystemTrayIcon() {
    if(!SystemTrayIcon) {
        Utils::MakeSmartPtr<QSystemTrayIcon>(SystemTrayIcon);
    }

    return SystemTrayIcon.get();
}

QMenu *Self::GetSystemTrayMenu() {
    if(!SystemTrayMenu) {
        Utils::MakeSmartPtr<QMenu>(SystemTrayMenu);
    }

    return SystemTrayMenu.get();
}