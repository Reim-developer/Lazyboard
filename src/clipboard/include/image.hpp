#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <QString>
#include <QMimeData>
#include <QSet>
#include <QClipboard>
#include <QTableWidget>
#include "../../zSQL/include/zSQL.hpp"
#include "../../zGui/include/zClipboardModel.hpp"

using zclipboard::zGui::zTableModel;
using zclipboard::zSQL::zManagerSQL;

namespace zclipboard::clipboard {
class zImage {
   public:
    static void addClipboardImage(zTableModel *zModelTable, QClipboard *clipboard,
                                  const zManagerSQL &zSQL, QSet<QString> &zExistingImages);
};
}  // namespace zclipboard::clipboard

#endif  // IMAGE_HPP