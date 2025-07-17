#include "Include/LayoutManager_Tookit.hpp"
#include "../../Utils/Include/Utils.hpp"
#include "Include/Layout_Tookit.hpp"

using ZClipboard::GUI::Toolkit::LayoutMangerTookit;
using ZClipboard::AppUtils::Utils;
using ZClipboard::GUI::Toolkit::WidgetProperty;

#define __SELF__ LayoutMangerTookit
#define __TOOKIT__ ComponentsToolkit
#define __WIDGET__ WidgetProperty

__SELF__ *__SELF__::StartBuild() {
    if(!Impl) {
        Utils::MakeSmartPtr<ImplData>(Impl);
    }

    return this;
}

__SELF__ *__SELF__::WhenDone() {
    return this;
}

__TOOKIT__ *__SELF__::GetTookit() {
    return this
        ->  Impl
        ->  tookit;
}

QGridLayout *__SELF__::GetGridLayout() {
    return this
        ->  Impl
        ->  layout;
}

__WIDGET__ __SELF__::GetTableViewLayout(__TOOKIT__ *tookit) {
    auto tableView = tookit->GetTableView();

    auto widgetLayout = Widget {
        .widget = tableView,
        .row = 1, .column = 0,
        .rowSpan = 1, .columnSpan = 5
    };

    return widgetLayout;
}

void __SELF__::SetupAppGridLayout() {
    auto tookit = this->GetTookit();
    auto layout = this->GetGridLayout();
    auto tableViewLayout = this->GetTableViewLayout(tookit);


    using Widget = WidgetProperty;
    GridLayoutAdd(layout, tableViewLayout);

    #if defined (Z_DEBUG)
        __LOG__
    #endif
}