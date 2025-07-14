#ifndef COMPONENTS_TOOLKIT_HPP
#define COMPONENTS_TOOLKIT_HPP
#include "../../../Utils/Include/Namespace_Macro.hpp"
#include "../../../Lib_Memory/Include/Memory.hpp"
#include "../../../Utils/Include/Utils.hpp"
#include "../../../GUI/Include/TableModel.hpp"
#include <QTableView>

using ZClipboard::AppUtils::Utils;
using ZClipboard::GUI::TableModel;
using ZClipboard::Lib_Memory::PtrUnique;

GUI_TOOLKIT_NAMESPACE

    class ComponentsToolkit {
        private:
            PtrUnique<QTableView> ClipboardTableView;
            PtrUnique<TableModel> ModelTable;

        public:
            QTableView *GetTableView();
            TableModel *GetTableModel();

    };

END_NAMESPACE

#endif // COMPONENTS_TOOLKIT_HPP