#ifndef TABLE_WIDGET_HXX
#define TABLE_WIDGET_HXX

#include <qcontainerfwd.h>
#include <qgridlayout.h>

#include <QGridLayout>
#include <QTableWidget>
#include <memory>
using std::unique_ptr;

namespace Lazyboard::front_end {
class TableWidget {
   public:
    TableWidget() noexcept;

   private:
    QStringList header_labels;
    static constexpr int DEFAULT_MAX_ROW = 10;

   private:
    unique_ptr<QTableWidget> table_widget;

   public:
    void setup_widget(QGridLayout* grid_layout);
};
}  // namespace Lazyboard::front_end

#endif  // TABLE_WIDGET_HXX