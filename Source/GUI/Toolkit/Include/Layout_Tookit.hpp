#ifndef LAYOUT_TOOLKIT_HPP
#define LAYOUT_TOOLKIT_HPP
#include "../../../Utils/Include/Namespace_Macro.hpp"
#include <utility>
#include <QGridLayout>
#include <QWidget>
#include <vector>
#include <type_traits>

using std::vector;
using std::forward;
using std::is_same_v;
using std::decay_t;

GUI_TOOLKIT_NAMESPACE

struct WidgetProperty {
    QWidget *widget;
    int row;
    int column;
    int rowSpan = 1;
    int columnSpan = 1;
};

template<typename T>
concept WgTypeTraits = is_same_v<decay_t<T>, WidgetProperty>;

template<WgTypeTraits ...Args>
void GridLayoutAdd(QGridLayout *widgetLayout, Args&&... args) {
    vector<WidgetProperty> widgetProperty = {
        std::forward<Args>(args)...
    };

    for(const auto &widget : widgetProperty) {
        widgetLayout->addWidget(widget.widget, widget.row, widget.column, widget.rowSpan, widget.columnSpan);
    }
}

END_NAMESPACE

#endif // LAYOUT_TOOLKIT_HPP