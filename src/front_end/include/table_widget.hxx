#ifndef TABLE_WIDGET_HXX
#define TABLE_WIDGET_HXX

#include <qcontainerfwd.h>
#include <qgridlayout.h>
#include <qheaderview.h>
#include <qtableview.h>

#include <QGridLayout>
#include <QTableWidget>
#include <memory>

#include "abstract_table_model.hxx"
using std::unique_ptr;

namespace Lazyboard::front_end {
class TableWidget {
   public:
	TableWidget() noexcept;

   private:
	QStringList header_labels;
	static constexpr int DEFAULT_MAX_ROW = 10;

   private:
	void set_resize_mode(QHeaderView *header);

   private:
	unique_ptr<QTableView> table_view_widget;
	unique_ptr<AbstractTableModel> abstract_table_model;

   public:
	void setup_widget(QGridLayout *grid_layout);
};
}  // namespace Lazyboard::front_end

#endif	// TABLE_WIDGET_HXX