#include "Include/TableView.hpp"
#include "../Clipboard/Include/ClipboardImage.hpp"
#include "../Clipboard/Include/ClipboardText.hpp"
#include "../Clipboard/Include/ClipboardCache.hpp"
#include "Include/ClipboardDialog.hpp"
#include "Include/TableModel.hpp"
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
using ZClipboard::Clipboard::ClipboardCache;
using ZClipboard::Clipboard::ClipboardImage;
using ZClipboard::Clipboard::ClipboardText;
using ZClipboard::Database::DatabaseManager;
using ZClipboard::GUI::TableView;
using ZClipboard::GUI::TableModel;

void TableView::SetupTableView(QWidget *zWindow, QGridLayout *zLayout) {
    databaseManager.setupinitDB();

    tableModel = new TableModel(databaseManager, this);
    tableView = new QTableView(zWindow);
    clipboard = QApplication::clipboard();

    tableView->setModel(tableModel);
    tableView->horizontalHeader()->setSectionResizeMode(TableModel::Time,
                                                         QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setSectionResizeMode(TableModel::Content,
                                                         QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(TableModel::Pin,
                                                         QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setSectionResizeMode(TableModel::ContentLength,
                                                         QHeaderView::ResizeToContents);

    tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
    tableView->setWordWrap(false);
    tableView->setTextElideMode(Qt::ElideRight);
    zLayout->addWidget(tableView, 1, 0, 1, 5);

    ClipboardCache clipboardCache;
    clipboardCache.addClipboardHistoryFromDB(tableModel, databaseManager);

    connect(tableView, &QTableView::clicked, this, &TableView::onContentClicked);
    connect(clipboard, &QClipboard::dataChanged, this, [this]() {
        const QMimeData *mimeData = clipboard->mimeData();

        if (mimeData->hasImage()) {
            if (!imageClipboard) imageClipboard = make_unique<ClipboardImage>();

            imageClipboard->addClipboardImage(tableModel, clipboard, databaseManager,existingImages);
            return;
        }

        if (!textClipboard) textClipboard = make_unique<ClipboardText>();
        textClipboard->addTextClipboard(tableModel, clipboard, databaseManager, existingContents);
    });
}

void TableView::onContentClicked(const QModelIndex &index) {
    if (!index.isValid() || index.column() != TableModel::Content) return;

    QString content = index.data(Qt::DisplayRole).toString();
    QString contentHash = index.data(Qt::UserRole).toString();

    if (content.isNull() || content.isEmpty()) {
        auto query = databaseManager.executeQueryResult(
            R"(
                SELECT image_data FROM clipboard WHERE content_hash = :hash
            )",
            {{"hash", contentHash}});

        if (query.next()) {
            QByteArray imageData = query.value(0).toByteArray();
            QImage image;
            image.loadFromData(imageData, "PNG");

            if (!image.isNull()) {
                if (!clipboardDialog) {
                    clipboardDialog = new ClipboardDialog();
                }

                clipboardDialog->showZImageDialog(image, tableView);
                return;
            }
        }
    }

    constexpr int MAX_LENGTH_CONTENT = 20;
    if (content.length() > MAX_LENGTH_CONTENT) {
        auto query = databaseManager.executeQueryResult(
            R"(
            SELECT content FROM clipboard WHERE content_hash = :hash
        )",
            {{"hash", contentHash}});

        query.exec();
        if (query.next()) content = query.value(0).toString();

        if (!clipboardDialog) {
            clipboardDialog = new ClipboardDialog();
        }

        clipboardDialog->showZContentDialog(content, tableView);
    }
}

TableModel *TableView::GetTableModel() {
    if (tableModel) return tableModel;

    return nullptr;
}

DatabaseManager &TableView::GetDatabase() {
    return databaseManager;
}

QClipboard *TableView::GetClipboard() {
    return clipboard;
}