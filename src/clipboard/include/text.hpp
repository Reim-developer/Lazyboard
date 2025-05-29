#ifndef TEXT_HPP
#define TEXT_HPP
#include <QSet>
#include <QString>
#include <QTableWidget>
#include <QTableView>
#include <QClipboard>
#include "../../zSQL/include/zSQL.hpp"
#include "../../zGui/include/zClipboardModel.hpp"

using zclipboard::zGui::zTableModel;
using zclipboard::zSQL::zManagerSQL;

namespace zclipboard::clipboard {
class zText {
   public:
    void addTextClipboard(zTableModel *zModelTable, QClipboard *clipboard, const zManagerSQL &zSQL,
                          QSet<QString> &zExistingTextHashes);
};
}  // namespace zclipboard::clipboard

#endif