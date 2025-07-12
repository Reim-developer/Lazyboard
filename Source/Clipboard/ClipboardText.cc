#include "Include/ClipboardText.hpp"
#include <QDateTime>
#include <QCryptographicHash>

using ZClipboard::Clipboard::ClipboardText;

void ClipboardText::addTextClipboard(TableModel *modelTable, QClipboard *clipboard,
                                     const DatabaseManager &database, 
                                     QSet<QString> &zExistingTextHashes) {
    QString content = clipboard->text();
    if (content.isEmpty()) return;

    QString contentHash = QString::fromUtf8(
        QCryptographicHash::hash(content.toUtf8(), QCryptographicHash::Sha1).toHex());

    if (zExistingTextHashes.contains(contentHash)) return;

    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    int textLength = content.length();
    int row = modelTable->rowCount();

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

    database.executeQuery(insertSQL, params);
    modelTable->addTextItem({
        .time = time,
        .content = content,
        .contentLength = textLength,
        .hash = contentHash,
    });
    zExistingTextHashes.insert(contentHash);
}
