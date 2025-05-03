#ifndef TEXT_HPP
#define TEXT_HPP
#include <QSet>
#include <QString>
#include <QTableWidget>
#include <QClipboard>
#include "../../zSQL/include/zSQL.hpp"

using namespace zclipboard::zSQL;

namespace zclipboard::clipboard {
    class zText {
        public:
            void addTextClipboard(QTableWidget *ztableWidget,QClipboard *zClipboard, 
                                  zManagerSQL zSQL, QSet<QString> &zExistingContents);
    };
} // namespace zclipboard::clipboard

#endif 