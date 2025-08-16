#ifndef ABSTRACT_TABLE_MODEL_HXX
#define ABSTRACT_TABLE_MODEL_HXX

#include <qabstractitemmodel.h>
#include <qcontainerfwd.h>
#include <qlist.h>
#include <qnamespace.h>
#include <qtmetamacros.h>
#include <qtpreprocessorsupport.h>
#include <qtypes.h>
#include <qvariant.h>

#include <algorithm>
#include <climits>
#include <cstdint>

using std::min;
using std::uint8_t;
namespace Lazyboard::front_end {

typedef struct TableItem {
	QString time;
	QString content;
	QString content_type;
	bool is_pinned = false;
} TableItem;

class AbstractTableModel : public QAbstractTableModel {
	Q_OBJECT

   public:
	// clang-format off
	enum Colum : uint8_t {
		TIME = 0,
		CONTENT = 1,
		TYPE = 2,
		PINNED,
		COLUMN_COUNT,
	};	// clang-format on

	int rowCount(const QModelIndex &parent = QModelIndex()) const override {
		Q_UNUSED(parent);
		return static_cast<int>(min(table_item.size(), qsizetype(INT_MAX)));
	}

	int columnCount(const QModelIndex &parent = QModelIndex()) const override {
		Q_UNUSED(parent);
		return COLUMN_COUNT;
	}

	QVariant data(const QModelIndex &index,
				  int role = Qt::DisplayRole) const override {
		if (!index.isValid() || index.row() >= table_item.size() ||
			index.row() < 0) {
			return QVariant();
		}

		const TableItem &item = table_item[index.row()];

		if (role == Qt::DisplayRole || role == Qt::EditRole) {
			switch (index.column()) {
				case TIME:
					return item.time;

				case CONTENT: {
					const auto max_length = 20;
					if (item.content.length() > max_length) {
						auto content_length = item.content.length();

						qsizetype remaining_length =
							content_length - max_length;

						QString truncated =
							item.content.left(max_length) +
							QString(" and %1 more...").arg(remaining_length);

						return truncated;
					}

					return item.content;
				}

				case TYPE | PINNED:
					return item.content_type;

				default:
					return {};
			}
		}

		if (role == Qt::CheckStateRole && index.column() == PINNED) {
			return item.is_pinned ? Qt::Checked : Qt::Unchecked;
		}

		return QVariant();
	}

	QVariant headerData(int section, Qt::Orientation orientation,
						int role = Qt::DisplayRole) const override {
		if (role != Qt::DisplayRole || orientation != Qt::Horizontal) {
			return QVariant();
		}

		switch (section) {
			case TIME:
				return "Time";

			case CONTENT:
				return "Content";

			case TYPE:
				return "Type";

			case PINNED:
				return "Pinned";

			default:
				return QVariant();
		}
	}

	Qt::ItemFlags flags(const QModelIndex &index) const override {
		if (!index.isValid()) {
			return Qt::NoItemFlags;
		}

		Qt::ItemFlags flag = QAbstractTableModel::flags(index);

		if (index.column() == PINNED) {
			flag |= Qt::ItemFlag::ItemIsUserCheckable |
					Qt::ItemFlag::ItemIsEditable;
		} else {
			flag |= Qt::ItemIsEditable;
		}

		return flag;
	}

	bool setData(const QModelIndex &index, const QVariant &value,
				 int role) override {
		if (!index.isValid() || index.row() >= table_item.size()) {
			return false;
		}

		TableItem &item = table_item[index.row()];

		if (index.column() == PINNED && role == Qt::CheckStateRole) {
			bool checked = (value.toInt() == Qt::Checked);

			if (item.is_pinned != checked) {
				item.is_pinned = checked;

				emit dataChanged(index, index,
								 {Qt::CheckStateRole, Qt::DisplayRole});

				return true;
			}
		}

		if (role == Qt::EditRole) {
			switch (index.column()) {
				case TIME:
					item.time = value.toString();
					break;

				case CONTENT:
					item.content = value.toString();
					break;

				case TYPE:
					item.content_type = value.toString();
					break;

				default:
					return false;
			}

			emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
			return true;
		}

		return false;
	}

   private:
	QList<TableItem> table_item;
};
}  // namespace Lazyboard::front_end

#endif	// ABSTRACT_TABLE_MODEL_HXX