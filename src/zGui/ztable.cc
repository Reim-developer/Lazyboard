#include "include/ztable.hpp"
#include "../clipboard/include/image.hpp"
#include "../clipboard/include/text.hpp"
#include "../clipboard/include/cache.hpp"
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

using namespace zclipboard::zgui;
using namespace zclipboard::clipboard;

ZTable::ZTable() {
    zSQLManager.connectToDB();
    
}

void ZTable::addZtable(QWidget *zWindow, QGridLayout *zLayout) {
    ztableWidget = new QTableWidget(zWindow);
    zClipboard = QApplication::clipboard();

    ztableWidget->setColumnCount(3);
    ztableWidget->setHorizontalHeaderLabels({"Time", "Content | Click to view", "Content Length"});

    ztableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ztableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ztableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    ztableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    zLayout->addWidget(ztableWidget, 0, 0);

    zCacheManager zCache;
    zCache.addClipboardHistoryFromDB(ztableWidget, zSQLManager);

    connect(ztableWidget, &QTableWidget::itemClicked, this, &ZTable::onContentClicked);
    connect(zClipboard, &QClipboard::dataChanged, this, [this]() {
        const QMimeData *mimeData = zClipboard->mimeData();

        if(mimeData->hasImage()) {
            zImage zClipboardImage;
            zClipboardImage.addClipboardImage(ztableWidget, zClipboard, zSQLManager, zExistingImages);
        } else {
            zText zClipboardText;
            zClipboardText.addTextClipboard(ztableWidget, zClipboard, zSQLManager, zExistingContents);
        }
    });
}

void ZTable::onContentClicked(QTableWidgetItem *ztableWidgetItem) {
    if(ztableWidgetItem->column() != CONTENT_COLUMN) return;

    QString content = ztableWidgetItem->text();
    zDialog = new ZDialog();
    zDialog->showZContentDialog(content, ztableWidget);
}

