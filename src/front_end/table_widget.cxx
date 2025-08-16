#include "include/table_widget.hxx"

#include <qabstractitemview.h>
#include <qgridlayout.h>
#include <qheaderview.h>
#include <qtableview.h>
#include <qtablewidget.h>

#include <memory>

#include "include/abstract_table_model.hxx"

using Lazyboard::front_end::AbstractTableModel;
using Lazyboard::front_end::TableWidget;
using std::make_unique;
using Self = TableWidget;

Self::TableWidget() noexcept {
	table_view_widget = make_unique<QTableView>();
	abstract_table_model = make_unique<AbstractTableModel>();
	header_labels = {"Time", "Content", "Type", "Pinned"};
}

void Self::set_resize_mode(QHeaderView *header) {
	header->setSectionResizeMode(AbstractTableModel::TIME,
								 QHeaderView::ResizeToContents);
	header->setSectionResizeMode(AbstractTableModel::CONTENT,
								 QHeaderView::Stretch);
	header->setSectionResizeMode(AbstractTableModel::TYPE,
								 QHeaderView::ResizeToContents);
	header->setSectionResizeMode(AbstractTableModel::PINNED,
								 QHeaderView::ResizeToContents);
}

void Self::setup_widget(QGridLayout *grid_layout) {
	table_view_widget->setModel(abstract_table_model.get());
	table_view_widget->setEditTriggers(QAbstractItemView::AllEditTriggers);

	auto header = table_view_widget->horizontalHeader();
	this->set_resize_mode(header);

	grid_layout->addWidget(table_view_widget.get(), 0, 0);
}