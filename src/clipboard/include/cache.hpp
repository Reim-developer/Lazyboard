#ifndef CACHE_HPP
#define CACHE_HPP
#include <QTableWidget>
#include "../../zSQL/include/zSQL.hpp"
#include "../../zGui/include/zClipboardModel.hpp"

using zclipboard::zSQL::zManagerSQL;
using zclipboard::zGui::zTableModel;

namespace zclipboard::clipboard {
    class zCacheManager {
        public:
            void addClipboardHistoryFromDB(zTableModel *zModelTable, zManagerSQL zSQL);
    };
} // namespace zclipboard::clipboard

#endif // CACHE_HPP