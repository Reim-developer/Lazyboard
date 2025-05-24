#include "include/cache.hpp"
#include "qobject.h"
#include <QtSql/QSqlQuery>
#include <QString>
#include <QImage>
#include <QByteArray>
#include <QTableWidgetItem>

using zclipboard::clipboard::zCacheManager;

void zCacheManager::addClipboardHistoryFromDB(zTableModel* zModelTable, const zManagerSQL& zSQL) {
    auto sqlQuery = zSQL.executeQueryResult(R"(
        --sql
        SELECT time, content, length, image_data, content_hash, is_pinned FROM clipboard
        ORDER BY time DESC
    )");

    while (sqlQuery->next()) {
        QString time = sqlQuery->value(0).toString();
        QString content = sqlQuery->value(1).toString();
        int contentLength = sqlQuery->value(2).toInt();
        QByteArray imageData = sqlQuery->value(3).toByteArray();
        QString contentHash = sqlQuery->value(4).toString();
        bool isPinned = (sqlQuery->value(5).toInt() == 1);

        QImage image;
        if (!imageData.isEmpty()) image.loadFromData(imageData, "PNG");

        if (!image.isNull()) {
            QPixmap pixmap = QPixmap::fromImage(image).scaled(128, 64, Qt::KeepAspectRatio);
            QTableWidgetItem* item = new QTableWidgetItem();
            zModelTable->addImageItem(
                {.time = time, .imageData = imageData, .hash = contentHash, .isPinned = isPinned});

        } else {
            zModelTable->addTextItem({.time = time,
                                      .content = content,
                                      .contentLength = contentLength,
                                      .hash = contentHash,
                                      .isPinned = isPinned});
        }
    }
}