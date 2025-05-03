#include "include/cache.hpp"
#include <QtSql/QSqlQuery>
#include <QString>
#include <QImage>
#include <QByteArray>
#include <QTableWidgetItem>

using namespace zclipboard::clipboard;

void zCacheManager::addClipboardHistoryFromDB(QTableWidget *ztableWidget, zManagerSQL zSQL) {
    QSqlQuery sqlQuery = zSQL.executeQueryResult(R"(
        --sql
        SELECT time, content, length, image_data, content_hash FROM clipboard
        ORDER BY time DESC
    )");

    while (sqlQuery.next()) {
        QString time = sqlQuery.value(0).toString();
        QString content = sqlQuery.value(1).toString();
        int contentLength = sqlQuery.value(2).toInt();
        QByteArray imageData = sqlQuery.value(3).toByteArray();
        QString imageHash = sqlQuery.value(4).toString();

        QImage image;
        if(!imageData.isEmpty()) image.loadFromData(imageData, "PNG");

        int row = ztableWidget->rowCount();
        ztableWidget->insertRow(row);
        ztableWidget->setItem(row, 0, new QTableWidgetItem(time));

        if(!image.isNull()) {
            QPixmap pixmap = QPixmap::fromImage(image).scaled(128, 64, Qt::KeepAspectRatio);
            QTableWidgetItem* item = new QTableWidgetItem();

            item->setData(Qt::UserRole, imageHash);
            item->setData(Qt::DecorationRole, pixmap);

            ztableWidget->setItem(row, 1, item);
        } else {
            ztableWidget->setItem(row, 1, new QTableWidgetItem(content));
        }

        ztableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(contentLength)));
    }
}