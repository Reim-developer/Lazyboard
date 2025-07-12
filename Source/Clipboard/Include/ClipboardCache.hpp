#ifndef CACHE_HPP
#define CACHE_HPP
#include <QTableWidget>
#include "../../Database/Include/DatabaseManager.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../../GUI/Include/TableModel.hpp"

using ZClipboard::GUI::TableModel;
using ZClipboard::Database::DatabaseManager;

CLIPBOARD_NAMESPACE

    class ClipboardCache {
    public:
        void addClipboardHistoryFromDB(TableModel *zModelTable, 
                                       const DatabaseManager &database);
    };

END_NAMESPACE

#endif  // CACHE_HPP