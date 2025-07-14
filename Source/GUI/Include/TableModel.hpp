#ifndef Z_CLIPBOARD_HPP
#define Z_CLIPBOARD_HPP
#include <QAbstractTableModel>
#include <QVariant>
#include <QString>
#include <QByteArray>
#include <QList>
#include "../../Database/Include/DatabaseManager.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"

using ZClipboard::Database::DatabaseManager;

GUI_NAMESPACE
    struct zClipboardItem {
        QString time;
        QString content;
        int contentLength;
        QByteArray imageData;
        QString hash;
        bool isPinned = false;
    };

    class TableModel : public QAbstractTableModel {
        Q_OBJECT

    public:
        enum Column { 
            Time = 0, 
            Content = 1, 
            ContentLength = 2, 
            Pin = 3, 
            ColumnCount = 4 
        };

        void SetupTableAbstract(DatabaseManager *database);

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QVariant headerData(int section, Qt::Orientation orientation,
                            int role = Qt::DisplayRole) const override;
        Qt::ItemFlags flags(const QModelIndex &index) const override;
        bool setData(const QModelIndex &index, const QVariant &value, int role) override;

        void addTextItem(const zClipboardItem &item);
        void addImageItem(const zClipboardItem &item);
        void clearData();
        void filterItems(const QString &searchText);

    private:
        QList<zClipboardItem> m_items;
        QList<zClipboardItem> mData;
        QSet<QString> m_existingHashes;
        DatabaseManager *databaseManager;
    };

END_NAMESPACE

#endif  // Z_CLIPBOARD_HPP
