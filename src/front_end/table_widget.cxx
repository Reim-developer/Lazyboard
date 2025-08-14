#include "include/table_widget.hxx"

#include <qgridlayout.h>
#include <qheaderview.h>
#include <qtablewidget.h>

#include <memory>

using Lazyboard::front_end::TableWidget;
using std::make_unique;
using Self = TableWidget;

Self::TableWidget() noexcept {
    table_widget = make_unique<QTableWidget>();
    header_labels = {"Time", "Content", "Type", "Pinned"};
}

void Self::setup_widget(QGridLayout* grid_layout) {
    table_widget->setRowCount(DEFAULT_MAX_ROW);
    table_widget->setColumnCount(4);
    table_widget->setHorizontalHeaderLabels(header_labels);
    table_widget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);

    grid_layout->addWidget(table_widget.get(), 0, 0);
}