#include "include/text.hpp"
#include <QDateTime>

using namespace zclipboard::clipboard;

void zText::addTextClipboard(QTableWidget *ztableWidget, QClipboard *zClipboard, 
                             zManagerSQL zSQL, QSet<QString> &zExistingContents) {
    QString text = zClipboard->text();
    if(text.isEmpty()) return;

    if(zExistingContents.contains(text)) return;

    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    int textLength = text.length();
    int row = ztableWidget->rowCount();

    ztableWidget->insertRow(row);
    ztableWidget->setItem(row, 0, new QTableWidgetItem(time));
    ztableWidget->setItem(row, 1, new QTableWidgetItem(text));
    ztableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(textLength)));

    zExistingContents.insert(text);

    QString insertSQL = R"(
        --sql
        INSERT INTO clipboard (time, content, length)
        VALUES(:time, :content, :length)
    )";

    QVariantMap params;
    params["time"] = time;
    params["content"] = text;
    params["length"] = textLength;

    zSQL.executeQuery(insertSQL, params);
}
