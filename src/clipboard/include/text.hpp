#ifndef TEXT_HPP
#define TEXT_HPP
#include <QSet>
#include <QString>
#include <QTableWidget>
#include <QTableView>
#include <QClipboard>
#include "../../zSQL/include/zSQL.hpp"
#include "../../zGui/include/zClipboardModel.hpp"

using zclipboard::zSQL::zManagerSQL;
using zclipboard::zGui::zTableModel;

namespace zclipboard::clipboard {
    class zText {
        public:
            void addTextClipboard(zTableModel *zModelTable,QClipboard *zClipboard, 
                                  zManagerSQL zSQL, QSet<QString> &zExistingTextHashes);
    };
} // namespace zclipboard::clipboard

#endif 