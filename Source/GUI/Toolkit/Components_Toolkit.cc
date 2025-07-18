#include "Include/Components_Toolkit.hpp"

using ZClipboard::GUI::Toolkit::ComponentsToolkit;
#define __SELF__ ComponentsToolkit

QTableView *__SELF__::GetTableView() {
    if(!ClipboardTableView) {
        Utils::MakeSmartPtr<QTableView>(ClipboardTableView);
    }

    return ClipboardTableView.get();
}

TableModel *__SELF__::GetTableModel() {
    if(!ModelTable) {
        Utils::MakeSmartPtr<TableModel>(ModelTable);
    }

    return ModelTable.get();
}

QLineEdit *__SELF__::GetSearchArea() {
    if(!SearchArea) {
        Utils::MakeSmartPtr<QLineEdit>(SearchArea);
    }

    return SearchArea.get();
}

QPushButton *__SELF__::GetClearButton() {
    if(!ClearButton) {
        Utils::MakeSmartPtr<QPushButton>(ClearButton);
    }

    return ClearButton.get();
}

QPushButton *__SELF__::GetDisconnectButton() {
    if(!DisconnectButton) {
        Utils::MakeSmartPtr<QPushButton>(DisconnectButton);
    }

    return DisconnectButton.get();
}

QPushButton *__SELF__::GetConnectButton() {
    if(!ConnectButton) {
        Utils::MakeSmartPtr<QPushButton>(ConnectButton);
    }

    return ConnectButton.get();
}