#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <QString>
#include <QMimeData>
#include <QSet>
#include <QClipboard>
#include <QTableWidget>
#include "../../Database/Include/DatabaseManager.hpp"
#include "../../GUI/Include/TableModel.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"

using ZClipboard::GUI::TableModel;
using ZClipboard::Database::DatabaseManager;

CLIPBOARD_NAMESPACE

   class ClipboardImage {
      public:
      static void addClipboardImage(TableModel *zModelTable, QClipboard *clipboard,
                                    const DatabaseManager &database, QSet<QString> &zExistingImages);
   };

END_NAMESPACE

#endif  // IMAGE_HPP