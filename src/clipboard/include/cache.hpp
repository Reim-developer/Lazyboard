#ifndef CACHE_HPP
#define CACHE_HPP
#include <QTableWidget>
#include "../../zSQL/include/zSQL.hpp"

using namespace zclipboard::zSQL;

namespace zclipboard::clipboard {
    class zCacheManager {
        public:
            void addClipboardHistoryFromDB(QTableWidget *ztableWidget, zManagerSQL zSQL);
    };
} // namespace zclipboard::clipboard

#endif // CACHE_HPP