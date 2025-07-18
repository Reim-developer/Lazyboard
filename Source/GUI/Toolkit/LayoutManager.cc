#include "Include/LayoutManager_Tookit.hpp"
#include "../../Utils/Include/Utils.hpp"
#include "Include/Layout_Tookit.hpp"

using ZClipboard::GUI::Toolkit::LayoutMangerTookit;
using ZClipboard::AppUtils::Utils;
using ZClipboard::GUI::Toolkit::WidgetProperty;

#define __SELF__ LayoutMangerTookit
#define __TOOKIT__ ComponentsToolkit
#define __WIDGET__ WidgetProperty
#define __LAYOUT__ QGridLayout

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

__LAYOUT__ *__SELF__::GetGridLayout() {
    return this
        ->  Impl
        ->  layout;
}

__WIDGET__ __SELF__::GetTableViewLayout(__TOOKIT__ *toolkit) {
    auto tableView = toolkit->GetTableView();

    auto widgetLayout = Widget {
        .widget = tableView,
        .row = 1, .column = 0,
        .rowSpan = 1, .columnSpan = 5
    };

    return widgetLayout;
}

__WIDGET__ __SELF__::GetSearchAreaLayout(__TOOKIT__ *toolkit) {
    auto searchArea = toolkit->GetSearchArea();

    auto widgetLayout = Widget {
        .widget = searchArea,
        .row = 0, .column = 0
    };

    return widgetLayout;
}

__WIDGET__ __SELF__::GetConnectButtonLayout(__TOOKIT__ *toolkit) {
    auto connectButton = toolkit->GetConnectButton();

    auto widgetLayout = __WIDGET__ {
        .widget = connectButton,
        .row = 0, .column = 1
    };

    return widgetLayout;
}

__WIDGET__ __SELF__::GetDisconnectButtonLayout(__TOOKIT__ *toolkit) {
    auto disconnectButton = toolkit->GetDisconnectButton();

    auto widgetLayout = __WIDGET__ {
        .widget = disconnectButton,
        .row = 0, .column = 4
    };

    return widgetLayout;
}

void __SELF__::SetupAppGridLayout() {
    auto toolkit = this->GetTookit();
    auto layout = this->GetGridLayout();

    /*
    * Widget layout information
    */
    auto tableViewLayout = this->GetTableViewLayout(toolkit);
    auto searchAreaLayout = this->GetSearchAreaLayout(toolkit);
    auto connectButtonLayout = this->GetConnectButtonLayout(toolkit);
    auto disconnectButtonLayout = this->GetDisconnectButtonLayout(toolkit);

    using Widget = WidgetProperty;
    GridLayoutAdd(layout, 
        tableViewLayout, searchAreaLayout,
        connectButtonLayout, disconnectButtonLayout
    );

    #if defined (Z_DEBUG)
        __LOG__
    #endif
}