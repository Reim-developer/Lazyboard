#include "include/text.hpp"
#include <QDateTime>
#include <QCryptographicHash>

using zclipboard::clipboard::zText;

void zText::addTextClipboard(zTableModel *zModelTable, QClipboard *clipboard,
                             const zManagerSQL &zSQL, QSet<QString> &zExistingTextHashes) {
    QString content = clipboard->text();
    if (content.isEmpty()) return;

    QString contentHash = QString::fromUtf8(
        QCryptographicHash::hash(content.toUtf8(), QCryptographicHash::Sha1).toHex());

    if (zExistingTextHashes.contains(contentHash)) return;

    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    int textLength = content.length();
    int row = zModelTable->rowCount();

    QString insertSQL = R"(
        --sql
        INSERT INTO clipboard (time, content, content_hash, length, is_pinned)
        VALUES(:time, :content, :content_hash, :length, 0)
    )";

    QVariantMap params;
    params["time"] = time;
    params["content"] = content;
    params["content_hash"] = contentHash;
    params["length"] = textLength;

    zSQL.executeQuery(insertSQL, params);
    zModelTable->addTextItem({
        .time = time,
        .content = content,
        .contentLength = textLength,
        .hash = contentHash,
    });
    zExistingTextHashes.insert(contentHash);
}
