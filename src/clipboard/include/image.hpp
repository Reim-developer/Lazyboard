#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <QString>
#include <QMimeData>
#include <QSet>
#include <QClipboard>
#include <QTableWidget>
#include "../../zSQL/include/zSQL.hpp"

using namespace zclipboard::zSQL;

namespace zclipboard::clipboard {
    class zImage {
        public:
            static void addClipboardImage(QTableWidget *ztableWidget, QClipboard *zClipboard, 
                                          zManagerSQL zSQL, QSet<QString> &zExistingImages);

    };
} // namespace zclipboard::clipboard

#endif // IMAGE_HPP