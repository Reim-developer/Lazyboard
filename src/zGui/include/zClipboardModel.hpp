#ifndef Z_CLIPBOARD_HPP
#define Z_CLIPBOARD_HPP
#include <QAbstractTableModel>
#include <QVariant>
#include <QString>
#include <QByteArray>
#include <QList>
#include "../../zSQL/include/zSQL.hpp"

using zclipboard::zSQL::zManagerSQL;

namespace zclipboard::zGui {
struct zClipboardItem {
    QString time;
    QString content;
    int contentLength;
    QByteArray imageData;
    QString hash;
    bool isPinned = false;
};

class zTableModel : public QAbstractTableModel {
    Q_OBJECT

   public:
    enum Column { Time = 0, Content = 1, ContentLength = 2, Pin = 3, ColumnCount = 4 };

    explicit zTableModel(zManagerSQL &zSQL, QObject *parent = nullptr);
    ~zTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    void addTextItem(const QString &time, const QString &text, const QString &hash, int length,
                     bool isPinned = false);
    void addImageItem(const QString &time, const QString &hash, const QByteArray &imageData,
                      bool isPinned = false);
    void clearData();
    void filterItems(const QString &searchText);

   public:
   private:
    QList<zClipboardItem> m_items;
    QList<zClipboardItem> mData;
    QSet<QString> m_existingHashes;

    zManagerSQL &m_SqlManager;
};
}  // namespace zclipboard::zGui

#endif  // Z_CLIPBOARD_HPP