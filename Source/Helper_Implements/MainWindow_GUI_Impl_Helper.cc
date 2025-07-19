#include "Include/MainWindow_GUI_Impl_Helper.hpp"

using ZClipboard::GUI::SearchAreaImpl;
using Impl = SearchAreaImpl;

void ClearButtonComponentImpl(Object *object, Toolkit *toolkit) {
    auto tableView = object
        ->  GetMainWindowObjects()
        ->  tableView_Component;

    object
        ->  GetMainWindowObjects()
        ->  clearButton_Component
        ->  SetupClearButton(toolkit, tableView);
}

void TableViewComponentImpl(Object *object, Toolkit *toolkit) {
    auto tableView = object
        ->  GetMainWindowObjects()
        ->  tableView_Component;

    tableView
        ->  UseToolkit(toolkit)
        ->  SetupTableView();
}

void SearchAreaComponentImpl(Object *object, Toolkit *toolkit) {
    auto tableView = object
        ->  GetMainWindowObjects()
        ->  tableView_Component;

    object
        ->  GetMainWindowObjects()
        ->  searchArea_Component
        ->  StartBuild()
        ->  WithAndThen(&Impl::tableView, tableView)
        ->  WithAndThen(&Impl::toolkit, toolkit)
        ->  WhenDone()
        ->  SetupSearchPanel();
}

void NotificationComponentImpl(Object *object, Toolkit *toolkit) {
    auto systemTrayIcon = toolkit->GetSystemTrayIcon();
    
    auto clipboard = object
        ->  GetMainWindowObjects()
        ->  tableView_Component
        ->  GetClipboard();

    object
        ->  GetMainWindowObjects()
        ->  notificationCore_Component
        ->  onClipboardChanged(systemTrayIcon, clipboard);
}

void SystemTrayComponentImpl(Object *object, Toolkit *toolkit, QIcon appIcon) {
    object
        ->  GetMainWindowObjects()
        ->  systemTray_Component
        ->  SetupSystemTray(&appIcon, toolkit);
}