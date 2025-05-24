#ifndef ZTABLE_HPP
#define ZTABLE_HPP
#include <QWidget>
#include <QGridLayout>
#include <QTableView>
#include <QObject>
#include <QClipboard>
#include <QDialog>
#include <QIcon>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QSet>
#include <QString>
#include <memory>
#include "zdialog.hpp"
#include "../../zSQL/include/zSQL.hpp"
#include "../../clipboard/include/image.hpp"
#include "../../clipboard/include/text.hpp"
#include "zClipboardModel.hpp"

#define CONTENT_COLUMN 1

using std::unique_ptr;
using zclipboard::clipboard::zImage;
using zclipboard::clipboard::zText;
using zclipboard::zGui::zTableModel;
using zclipboard::zSQL::zManagerSQL;

namespace zclipboard::zGui {
class ZTable : public QObject {
    Q_OBJECT

   public:
    ZTable();
    ~ZTable();

    void addZtable(QWidget *zWindow, QGridLayout *zLayout);
    zTableModel *getZModel();
    zManagerSQL &getZSQL();
    QClipboard *getClipboard();

   private:
    QClipboard *zClipboard;
    QTableView *zTableView;
    zTableModel *zModelTable;

    unique_ptr<zImage> imageClipboard;
    unique_ptr<zText> textClipboard;

    QSet<QString> zExistingContents;
    QSet<QString> zExistingImages;

    zManagerSQL zSQLManager;
    ZDialog *zDialog;

   public slots:
    void onContentClicked(const QModelIndex &current);
};
}  // namespace zclipboard::zGui

#endif