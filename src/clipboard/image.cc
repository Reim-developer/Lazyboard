#include "include/image.hpp"
#include <QBuffer>
#include <QCryptographicHash>
#include <QDateTime>

using namespace zclipboard::clipboard;

void zImage::addClipboardImage(zTableModel *zModelTable, QClipboard *zClipboard, zManagerSQL zSQL,
                               QSet<QString> &zExistingImages) {
    const QMimeData *mimeData = zClipboard->mimeData();
    if (!mimeData || !mimeData->hasImage()) return;

    QImage clipboardImage = qvariant_cast<QImage>(mimeData->imageData());
    if (clipboardImage.isNull()) return;

    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    clipboardImage.save(&buffer, "PNG");

    QString imageHash =
        QString::fromUtf8(QCryptographicHash::hash(imageData, QCryptographicHash::Sha1).toHex());

    if (zExistingImages.contains(imageHash)) return;

    QPixmap pixMap = QPixmap::fromImage(clipboardImage)
                         .scaled(64, 64, Qt::KeepAspectRatio, Qt::FastTransformation);
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    int imageSize = imageData.size();

    QString insertSQL = R"(
        --sql
        INSERT INTO clipboard (time, content, content_hash, length, image_data, is_pinned)
        VALUES (:time, :content, :hash, :length, :image_data, 0)
    )";

    QVariantMap params;
    params["time"] = time;
    params["content"] = "[Image]";
    params["hash"] = imageHash;
    params["length"] = imageSize;
    params["image_data"] = imageData;

    zSQL.executeQuery(insertSQL, params);

    zModelTable->addImageItem(time, imageHash, imageData);
    zExistingImages.insert(imageHash);
}
