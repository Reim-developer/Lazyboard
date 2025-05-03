#include "include/image.hpp"
#include <QBuffer>
#include <QCryptographicHash>
#include <QDateTime>

using namespace zclipboard::clipboard;

void zImage::addClipboardImage(QTableWidget *ztableWidget, QClipboard *zClipboard,
                               zManagerSQL zSQL, QSet<QString> &zExistingImages) {
    const QMimeData *mimeData = zClipboard->mimeData();
    if(!mimeData || !mimeData->hasImage()) return;

    QImage clipboardImage = qvariant_cast<QImage>(mimeData->imageData());
    if(clipboardImage.isNull()) return;

    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);

    clipboardImage.save(&buffer, "PNG");
    QString imageHash = QString::fromUtf8(
        QCryptographicHash::hash(imageData, 
            QCryptographicHash::Sha1).toHex()
    );

    if(zExistingImages.contains(imageHash)) return;

    QPixmap pixMap = QPixmap::fromImage(clipboardImage).scaled(
        64, 64, Qt::KeepAspectRatio
    );
    QTableWidgetItem *imageWidgetItem = new QTableWidgetItem();
    imageWidgetItem->setData(Qt::UserRole, imageHash);
    imageWidgetItem->setData(Qt::DecorationRole, pixMap);

    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    int imageSize = imageData.size();

    int row = ztableWidget->rowCount();
    ztableWidget->insertRow(row);
    ztableWidget->setItem(row, 0, new QTableWidgetItem(time));
    ztableWidget->setItem(row, 1, imageWidgetItem);
    ztableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(imageSize)));

    QString insertSQL = R"(
        --sql
        INSERT INTO clipboard (time, content, content_hash, length, image_data)
        VALUES (:time, :content, :hash, :length, :image_data)
    )";

    QVariantMap params;
    params["time"] = time;
    params["content"] = "[Image]";
    params["hash"] = imageHash;
    params["length"] = imageSize;
    params["image_data"] = imageData;

    zSQL.executeQuery(insertSQL, params);
    zExistingImages.insert(imageHash);
}
