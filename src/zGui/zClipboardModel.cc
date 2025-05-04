#include "include/zClipboardModel.hpp"
#include <QImage>
#include <QPixmap>

using zclipboard::zGui::zTableModel;

zTableModel::zTableModel(QObject *parent) : QAbstractTableModel(parent) {

}

zTableModel::~zTableModel() {}

int zTableModel::rowCount(const QModelIndex &) const {
    return m_items.size();
}

int zTableModel::columnCount(const QModelIndex &) const {
    return ColumnCount;
}

QVariant zTableModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid() || index.row() >= m_items.size())
        return QVariant();

    const zClipboardItem &item = m_items[index.row()];

    if(role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case Time: return item.time;
            case Content:
                if(item.content.length() > 100) return "[Too many content, click to view]";
            
            return item.content;

            case ContentLength: return item.contentLength;
            default: return QVariant();
        }
    }   else if (role == Qt::DecorationRole 
              && index.column() == Content && !item.imageData.isEmpty()) {
            
            QImage image;
            image.loadFromData(item.imageData, "PNG");
            return QPixmap::fromImage(image).scaled(32, 32, Qt::KeepAspectRatio);
    }   
    else if(role == Qt::UserRole && index.column() == Content)  return item.hash;
    
    return QVariant();
}

QVariant zTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch(section) {
            case Time: return "Time";
            case Content: return "Content  | Click to view";
            case ContentLength: return "Content Length";
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

void zTableModel::addTextItem(const QString &time, const QString& text, const QString& hash, int length) {
    if(m_existingHashes.contains(hash)) return;

    beginInsertColumns(QModelIndex(), rowCount(), rowCount());

    zClipboardItem clipboardItem;
    clipboardItem.time = time;
    clipboardItem.content = text;
    clipboardItem.contentLength = length;
    clipboardItem.hash = hash;

    m_items.append(clipboardItem);
    m_existingHashes.insert(hash);
    
    endInsertRows();    
}
