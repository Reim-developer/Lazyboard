#ifndef CACHE_HPP
#define CACHE_HPP
#include <QTableWidget>
#include "../../zSQL/include/zSQL.hpp"
#include "../../zGui/include/zClipboardModel.hpp"

using zclipboard::zGui::zTableModel;
using zclipboard::zSQL::zManagerSQL;

namespace zclipboard::clipboard {
class zCacheManager {
   public:
    void addClipboardHistoryFromDB(zTableModel *zModelTable, const zManagerSQL &zSQL);
};
}  // namespace zclipboard::clipboard

#endif  // CACHE_HPP