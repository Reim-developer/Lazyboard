#include "include/ztable.hpp"
#include "../clipboard/include/image.hpp"
#include "../clipboard/include/text.hpp"
#include "../clipboard/include/cache.hpp"
#include "../encryption/include/encryption.hpp"
#include "../encryption/include/dialog_info.hpp"
#include "include/zClipboardModel.hpp"
#include "../core/include/enum.hpp"
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
#include <memory>

using std::make_unique;
using zclipboard::clipboard::zCacheManager;
using zclipboard::clipboard::zImage;
using zclipboard::clipboard::zText;
using zclipboard::core::HashState;
using zclipboard::encryption::DialogInfo;
using zclipboard::encryption::EncryptionManager;
using zclipboard::zGui::ZTable;
using zclipboard::zGui::zTableModel;

void ZTable::setupDatabase(QWidget *parent) {
    unique_ptr<EncryptionManager> encryption = make_unique<EncryptionManager>();

    const auto HASH_STATE = encryption->addHashFile();
    if (HASH_STATE == HashState::DELETED) {
        unique_ptr<DialogInfo> dialogInfo = make_unique<DialogInfo>();

        dialogInfo->showHashError(parent);
    }

    zSQLManager.setupinitDB();
}

void ZTable::addZtable(QWidget *zWindow, QGridLayout *zLayout) {
    setupDatabase(zWindow);

    zModelTable = new zTableModel(zSQLManager, this);
    zTableView = new QTableView(zWindow);
    clipboard = QApplication::clipboard();

    zTableView->setModel(zModelTable);
    zTableView->horizontalHeader()->setSectionResizeMode(zTableModel::Time,
                                                         QHeaderView::ResizeToContents);
    zTableView->horizontalHeader()->setSectionResizeMode(zTableModel::Content,
                                                         QHeaderView::Stretch);
    zTableView->horizontalHeader()->setSectionResizeMode(zTableModel::Pin,
                                                         QHeaderView::ResizeToContents);
    zTableView->horizontalHeader()->setSectionResizeMode(zTableModel::ContentLength,
                                                         QHeaderView::ResizeToContents);

    zTableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
    zTableView->setWordWrap(false);
    zTableView->setTextElideMode(Qt::ElideRight);
    zLayout->addWidget(zTableView, 1, 0, 1, 5);

    zCacheManager zCache;
    zCache.addClipboardHistoryFromDB(zModelTable, zSQLManager);

    connect(zTableView, &QTableView::clicked, this, &ZTable::onContentClicked);
    connect(clipboard, &QClipboard::dataChanged, this, [this]() {
        const QMimeData *mimeData = clipboard->mimeData();

        if (mimeData->hasImage()) {
            if (!imageClipboard) imageClipboard = make_unique<zImage>();

            imageClipboard->addClipboardImage(zModelTable, clipboard, zSQLManager,
                                              zExistingContents);
            return;
        }

        if (!textClipboard) textClipboard = make_unique<zText>();
        textClipboard->addTextClipboard(zModelTable, clipboard, zSQLManager, zExistingContents);
    });
}

void ZTable::onContentClicked(const QModelIndex &index) {
    if (!index.isValid() || index.column() != zTableModel::Content) return;

    QString content = index.data(Qt::DisplayRole).toString();
    QString contentHash = index.data(Qt::UserRole).toString();

    if (content.isNull() || content.isEmpty()) {
        auto query = zSQLManager.executeQueryResult(
            R"(
                SELECT image_data FROM clipboard WHERE content_hash = :hash
            )",
            {{"hash", contentHash}});

        if (query.next()) {
            QByteArray imageData = query.value(0).toByteArray();
            QImage image;
            image.loadFromData(imageData, "PNG");

            if (!image.isNull()) {
                if (!zDialog) {
                    zDialog = new ZDialog();
                }

                zDialog->showZImageDialog(image, zTableView);
                return;
            }
        }
    }

    constexpr int MAX_LENGTH_CONTENT = 20;
    if (content.length() > MAX_LENGTH_CONTENT) {
        auto query = zSQLManager.executeQueryResult(
            R"(
            SELECT content FROM clipboard WHERE content_hash = :hash
        )",
            {{"hash", contentHash}});

        query.exec();
        if (query.next()) content = query.value(0).toString();

        if (!zDialog) {
            zDialog = new ZDialog();
        }

        zDialog->showZContentDialog(content, zTableView);
    }
}

zTableModel *ZTable::getZModel() {
    if (zModelTable) return zModelTable;

    return nullptr;
}

zManagerSQL &ZTable::getZSQL() {
    return zSQLManager;
}

QClipboard *ZTable::getClipboard() {
    return clipboard;
}