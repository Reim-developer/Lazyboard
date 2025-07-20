#include "Include/MainWindow_LayoutManager.hpp"
#include "../../Utils/Include/Utils.hpp"
#include "Include/Layout_Toolkit.hpp"

using ZClipboard::GUI::Toolkit::MainWindowLayoutManager;
using ZClipboard::AppUtils::Utils;
using ZClipboard::GUI::Toolkit::WidgetProperty;

using Self = MainWindowLayoutManager;
using Toolkit = MainWindowComponentsManager;
using Widget = WidgetProperty;
using Layout = QGridLayout;

Self *Self::StartBuild() {
    if(!Impl) {
        Utils::MakeSmartPtr<ImplData>(Impl);
    }

    return this;
}

Self *Self::WhenDone() {
    return this;
}

Toolkit *Self::GetTookit() {
    return this
        ->  Impl
        ->  tookit;
}

Layout *Self::GetGridLayout() {
    return this
        ->  Impl
        ->  layout;
}

Widget Self::GetTableViewLayout(Toolkit *toolkit) {
    auto tableView = toolkit->GetTableView();

    auto widgetLayout = Widget {
        .widget = tableView,
        .row = 1, .column = 0,
        .rowSpan = 1, .columnSpan = 5
    };

    return widgetLayout;
}

Widget Self::GetSearchAreaLayout(Toolkit *toolkit) {
    auto searchArea = toolkit->GetSearchArea();

    auto widgetLayout = Widget {
        .widget = searchArea,
        .row = 0, .column = 0
    };

    return widgetLayout;
}

Widget Self::GetConnectButtonLayout(Toolkit *toolkit) {
    auto connectButton = toolkit->GetConnectButton();

    auto widgetLayout = Widget {
        .widget = connectButton,
        .row = 0, .column = 1
    };

    return widgetLayout;
}

Widget Self::GetDisconnectButtonLayout(Toolkit *toolkit) {
    auto disconnectButton = toolkit->GetDisconnectButton();

    auto widgetLayout = Widget {
        .widget = disconnectButton,
        .row = 0, .column = 4
    };

    return widgetLayout;
}

Widget Self::GetClearButtonLayout(Toolkit *toolkit) {
    auto clearButton = toolkit->GetClearButton();

    auto widgetLayout = Widget {
        .widget = clearButton,
        .row = 0, .column = 2
    };

    return widgetLayout;
}

Widget Self::GetSettingButtonLayout(Toolkit *toolkit) {
    auto settingButton = toolkit->GetSettingButton();

    auto widgetLayout = Widget {
        .widget = settingButton,
        .row = 0, .column = 3
    };

    return widgetLayout;
}

void Self::SetupAppGridLayout() {
    auto toolkit = this->GetTookit();
    auto layout = this->GetGridLayout();
    
    /*
    * Widget layout information
    */
    auto tableViewLayout = this->GetTableViewLayout(toolkit);
    auto searchAreaLayout = this->GetSearchAreaLayout(toolkit);
    auto connectButtonLayout = this->GetConnectButtonLayout(toolkit);
    auto disconnectButtonLayout = this->GetDisconnectButtonLayout(toolkit);
    auto clearButtonLayout = this->GetClearButtonLayout(toolkit);
    auto settingButtonLayout = this->GetSettingButtonLayout(toolkit);

    using Widget = WidgetProperty;
    GridLayoutAdd(layout, 
        tableViewLayout, searchAreaLayout,
        connectButtonLayout, disconnectButtonLayout,
        clearButtonLayout, settingButtonLayout
    );

    #if defined (Z_DEBUG)
        __LOG__
    #endif
}