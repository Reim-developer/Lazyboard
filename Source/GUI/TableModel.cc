#include "Include/TableModel.hpp"
#include "../Language/Include/Language.hpp"
#include "../Language/Include/Translate.hpp"
#include "../Utils/Include/Settings.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Utils/Include/Utils.hpp"
#include <QImage>
#include <QPixmap>
#include <QSettings>

using ZClipboard::Language::Translate;
using ZClipboard::GUI::TableModel;
using ZClipboard::Database::DatabaseManager;
using ZClipboard::AppUtils::Utils;

void TableModel::SetupTableAbstract(DatabaseManager *database) {
    this->databaseManager = database;
}

int TableModel::rowCount(const QModelIndex &) const {
    return mData.size();
}

int TableModel::columnCount(const QModelIndex &) const {
    return ColumnCount;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= mData.size() || index.row() < 0) return QVariant();

    const zClipboardItem &item = mData[index.row()];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case Time:
                return item.time;

            case Content:
                if (!item.imageData.isEmpty()) return QVariant();

                if (item.content.length() > 20) {
                    int remainingLength = item.content.length() - 20;
                    QString truncated =
                        item.content.left(20) + QString(" and %1 more...").arg(remainingLength);

                    return truncated;
                }

                return item.content;

            case ContentLength:
                return item.contentLength;

            case Pin:
                return {};

            default:
                return {};
        }
    }
    if (role == Qt::DecorationRole && index.column() == Content && !item.imageData.isEmpty()) {
        QImage image;
        image.loadFromData(item.imageData, "PNG");

        return QPixmap::fromImage(image).scaled(128, 128, Qt::KeepAspectRatio);
    }

    if (role == Qt::UserRole && index.column() == Content) return item.hash;

    if (role == Qt::CheckStateRole && index.column() == Pin)
        return item.isPinned ? Qt::Checked : Qt::Unchecked;

    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        QSettings settings(AUTHOR_NAME, APP_NAME);

        if (!Utils::hasSetting(LANGUAGE_SETTING)) {
            settings.setValue(LANGUAGE_SETTING, Translate::ENGLISH);
        }

        const int LANGUAGE_TYPE = settings.value(LANGUAGE_SETTING).toInt();
        switch (LANGUAGE_TYPE) {
            case Translate::ENGLISH:
                switch (section) {
                    case Time:
                        return TABLE_TIME_EN;
                    case Content:
                        return TABLE_CONTENT_EN;
                    case ContentLength:
                        return TABLE_CONTENT_LENGTH_EN;
                    case Pin:
                        return TABLE_PIN_EN;
                }
                break;

            case Translate::VIETNAMESE:
                switch (section) {
                    case Time:
                        return TABLE_TIME_VI;
                    case Content:
                        return TABLE_CONTENT_VI;
                    case ContentLength:
                        return TABLE_CONTENT_LENGTH_VI;
                    case Pin:
                        return TABLE_PIN_VI;
                }
                break;
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

void TableModel::addTextItem(const zClipboardItem &item) {
    if (m_existingHashes.contains(item.hash)) return;

    if (item.hash.isEmpty()) {
        return;
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    zClipboardItem clipboardItem;
    clipboardItem.time = item.time;
    clipboardItem.content = item.content;
    clipboardItem.contentLength = item.contentLength;
    clipboardItem.hash = item.hash;
    clipboardItem.isPinned = item.isPinned;

    m_items.append(clipboardItem);
    mData.append(clipboardItem);
    m_existingHashes.insert(item.hash);

    endInsertRows();
}

void TableModel::addImageItem(const zClipboardItem &item) {
    if (m_existingHashes.contains(item.hash)) return;
    if (item.hash.isEmpty()) {
        return;
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    zClipboardItem clipboardItem;
    clipboardItem.time = item.time;
    clipboardItem.content = "";
    clipboardItem.contentLength = item.imageData.size();
    clipboardItem.imageData = item.imageData;
    clipboardItem.hash = item.hash;
    clipboardItem.isPinned = item.isPinned;

    m_items.append(clipboardItem);
    mData.append(clipboardItem);
    m_existingHashes.insert(item.hash);
    endInsertRows();
}

void TableModel::clearData() {
    beginResetModel();
    mData.clear();
    m_items.clear();
    m_existingHashes.clear();
    endResetModel();
}

void TableModel::filterItems(const QString &searchText) {
    beginResetModel();

    if (searchText.isEmpty()) {
        mData = m_items;
    } else {
        QList<zClipboardItem> filteredData;
        for (const auto &item : m_items) {
            if (item.content.contains(searchText, Qt::CaseInsensitive) ||
                item.hash.contains(searchText, Qt::CaseInsensitive))
                filteredData.append(item);
        }
        mData = filteredData;
    }

    endResetModel();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.column() == Pin) flags |= Qt::ItemIsUserCheckable;
    return flags;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || role != Qt::CheckStateRole || index.column() != Pin) return false;

    if (index.row() >= mData.size() || index.row() < 0) {
        return false;
    }

    zClipboardItem itemToModify = mData[index.row()];
    bool newPinState = (value.toInt() == Qt::Checked);

    if (newPinState == itemToModify.isPinned) {
        return true;
    }

    itemToModify.isPinned = newPinState;

    const int oldRow = index.row();
    int targetRow = 0;

    if (!itemToModify.isPinned) {
        targetRow = 0;
        while (targetRow < mData.size() && mData[targetRow].isPinned) {
            targetRow++;
        }

        if (oldRow < targetRow) {
            targetRow--;
        }
    } else {
        targetRow = 0;
    }

    const QString hashToUpdate = itemToModify.hash;
    if (!hashToUpdate.isEmpty()) {
        databaseManager->updatePinStatus(hashToUpdate, itemToModify.isPinned);
    }

    if (oldRow != targetRow) {
        if (targetRow < 0) {
            targetRow = 0;
        }

        if (targetRow > mData.size()) {
            targetRow = mData.size();
        }

        int effectiveTargetRow = (oldRow < targetRow) ? targetRow + 1 : targetRow;

        if (!beginMoveRows(QModelIndex(), oldRow, oldRow, QModelIndex(), effectiveTargetRow)) {
            mData[oldRow].isPinned = !newPinState;
            emit dataChanged(index, index, {Qt::CheckStateRole});

            return false;
        }

        zClipboardItem movedItem = mData.takeAt(oldRow);

        movedItem.isPinned = newPinState;
        mData.insert(targetRow, movedItem);

        endMoveRows();

        QModelIndex topLeft = createIndex(targetRow, 0);
        QModelIndex bottomRight = createIndex(targetRow, columnCount() - 1);

        if (topLeft.isValid() && bottomRight.isValid()) {
            emit dataChanged(topLeft, bottomRight, {Qt::CheckStateRole});
        }
    } else {
        mData[oldRow].isPinned = itemToModify.isPinned;
        emit dataChanged(index, index, {Qt::CheckStateRole});
    }

    return true;
}
