#include "Include/Components_Toolkit.hpp"

using ZClipboard::GUI::Toolkit::ComponentsToolkit;

QTableView *ComponentsToolkit::GetTableView() {
    if(!ClipboardTableView) {
        Utils::MakeSmartPtr<QTableView>(ClipboardTableView);
    }

    return ClipboardTableView.get();
}

TableModel *ComponentsToolkit::GetTableModel() {
    if(!ModelTable) {
        Utils::MakeSmartPtr<TableModel>(ModelTable);
    }

    return ModelTable.get();
}