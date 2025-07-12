#ifndef TEXT_HPP
#define TEXT_HPP
#include <QSet>
#include <QString>
#include <QTableWidget>
#include <QTableView>
#include <QClipboard>
#include "../../Database/Include/DatabaseManager.hpp"
#include "../../GUI/Include/TableModel.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"

using ZClipboard::GUI::TableModel;
using ZClipboard::Database::DatabaseManager;

CLIPBOARD_NAMESPACE

   class ClipboardText {
      public:
      void addTextClipboard(TableModel *zModelTable, QClipboard *clipboard, 
                           const DatabaseManager &database,
                           QSet<QString> &zExistingTextHashes);
   };

END_NAMESPACE
#endif