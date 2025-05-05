#include "include/zClipboardModel.hpp"
#include <QImage>
#include <QPixmap>

using zclipboard::zGui::zTableModel;

zTableModel::zTableModel(QObject *parent) : QAbstractTableModel(parent) {}

zTableModel::~zTableModel() {}

int zTableModel::rowCount(const QModelIndex &) const {
    return mData.size();
}

int zTableModel::columnCount(const QModelIndex &) const {
    return ColumnCount;
}

QVariant zTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= mData.size()) return QVariant();

    const zClipboardItem &item = mData[index.row()];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case Time:
                return item.time;

            case Content:
                if (!item.imageData.isEmpty()) return QVariant();
                if (item.content.length() > 20) {
                    int remainingLength = item.content.length() - 20;
                    QString truncated = item.content.left(20) + QString(" and %1 more...").arg(remainingLength);

                    return truncated;
                }

                return item.content;

            case ContentLength:
                return item.contentLength;
            default:
                return QVariant();
        }
    } else if (role == Qt::DecorationRole && index.column() == Content && !item.imageData.isEmpty()) {
        QImage image;
        image.loadFromData(item.imageData, "PNG");
        return QPixmap::fromImage(image).scaled(128, 128, Qt::KeepAspectRatio);
    } else if (role == Qt::UserRole && index.column() == Content)
        return item.hash;

    return QVariant();
}

QVariant zTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case Time:
                return "Time";
            case Content:
                return "Content  | Click to view";
            case ContentLength:
                return "Content Length";
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

void zTableModel::addTextItem(const QString &time, const QString &text, const QString &hash, int length) {
    if (m_existingHashes.contains(hash)) return;

    beginInsertColumns(QModelIndex(), rowCount(), rowCount());

    zClipboardItem clipboardItem;
    clipboardItem.time = time;
    clipboardItem.content = text;
    clipboardItem.contentLength = length;
    clipboardItem.hash = hash;

    m_items.append(clipboardItem);
    mData.append(clipboardItem);
    m_existingHashes.insert(hash);

    endInsertRows();
}

void zTableModel::addImageItem(const QString &time, const QString &hash, const QByteArray &imageData) {
    if (m_existingHashes.contains(hash)) return;

    beginInsertColumns(QModelIndex(), rowCount(), rowCount());

    zClipboardItem clipboardItem;
    clipboardItem.time = time;
    clipboardItem.content = "";
    clipboardItem.contentLength = imageData.size();
    clipboardItem.imageData = imageData;
    clipboardItem.hash = hash;

    m_items.append(clipboardItem);
    mData.append(clipboardItem);
    m_existingHashes.insert(hash);
    endInsertRows();
}

void zTableModel::clearData() {
    beginResetModel();

    mData.clear();
    m_items.clear();

    endResetModel();
}

void zTableModel::filterItems(const QString &searchText) {
    QList<zClipboardItem> filteredData;

    for (const auto &item : m_items) {
        if (item.content.contains(searchText) || item.hash.contains(searchText)) filteredData.append(item);
    }

    beginResetModel();
    mData = filteredData;
    endResetModel();
}
