#include "include/ztable.hpp"
#include "../clipboard/include/image.hpp"
#include "../clipboard/include/text.hpp"
#include "../clipboard/include/cache.hpp"
#include "include/zClipboardModel.hpp"
#include <QTableWidget>
#include <QHeaderView>
#include <QDateTime>
#include <QClipboard>
#include <QApplication>
#include <QTableWidgetItem>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTimer>
#include <QMimeData>
#include <QPointer>
#include <QImage>
#include <QByteArray>
#include <QCryptographicHash>
#include <QBuffer>
#include <QPixmap>

using zclipboard::zGui::ZTable;
using zclipboard::clipboard::zCacheManager;
using zclipboard::zGui::zTableModel;
using zclipboard::clipboard::zImage;
using zclipboard::clipboard::zText;

ZTable::ZTable() {
    zSQLManager.connectToDB();
    
}

void ZTable::addZtable(QWidget *zWindow, QGridLayout *zLayout) {
    zModelTable = new zTableModel(this);
    zTableView = new QTableView(zWindow);
    zClipboard = QApplication::clipboard();
    zTableView->setModel(zModelTable);

    zTableView->horizontalHeader()->setSectionResizeMode(
        zTableModel::Time, QHeaderView::ResizeToContents
    );
    zTableView->horizontalHeader()->setSectionResizeMode(
        zTableModel::Content, QHeaderView::Stretch
    );
    zTableView->horizontalHeader()->setSectionResizeMode(
        zTableModel::ContentLength, QHeaderView::ResizeToContents
    );

    zTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    zLayout->addWidget(zTableView, 1, 0);

    zCacheManager zCache;
    zCache.addClipboardHistoryFromDB(zModelTable, zSQLManager);

    connect(zTableView, &QTableView::clicked, this, &ZTable::onContentClicked);
    connect(zClipboard, &QClipboard::dataChanged, this, [this]() {
        const QMimeData *mimeData = zClipboard->mimeData();

        if(mimeData->hasImage()) {
            // zImage zClipboardImage;
            // zClipboardImage.addClipboardImage(zModelTable, zClipboard, zSQLManager, zExistingImages);
        } else {
            zText zClipboardText;
            zClipboardText.addTextClipboard(zModelTable, zClipboard, zSQLManager, zExistingContents);
        }
    });
}

void ZTable::onContentClicked(const QModelIndex &index) {
  
    if(!index.isValid() || index.column() != zTableModel::Content) return;
    
    QString content = index.data(Qt::DisplayRole).toString();
    QString contentHash = index.data(Qt::UserRole).toString();

    if(content == "[Too many content, click to view]") {
        QSqlQuery query = zSQLManager.executeQueryResult(R"(
            SELECT content FROM clipboard WHERE content_hash = :hash
        )", {{"hash", contentHash}});
        
        query.exec();
        query.next();
        content = query.value(0).toString();
    }

    zDialog = new ZDialog();
    zDialog->showZContentDialog(content, zTableView);
}

