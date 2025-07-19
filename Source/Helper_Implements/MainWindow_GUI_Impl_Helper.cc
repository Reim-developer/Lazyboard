#include "Include/MainWindow_GUI_Impl_Helper.hpp"

using ZClipboard::GUI::SearchAreaImpl;
using Impl = SearchAreaImpl;
using Window = QMainWindow;

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

void SystemTrayComponentImpl(Window *window, Object *object, Toolkit *toolkit, QIcon appIcon) {
    object
        ->  GetMainWindowObjects()
        ->  systemTray_Component
        ->  SetupSystemTray(window, &appIcon, toolkit);
}

void ConnectButtonComponentImpl(Window *window, Object *object, Toolkit *toolkit) {
    object
        ->  GetMainWindowObjects()
        ->  connectButton_Component
        ->  SetupConnectButton(window, toolkit);
}

void DisconnectButtonComponentImpl(Window *window, Object *object, Toolkit *toolkit) {
    auto connectButton = object
        ->  GetMainWindowObjects()
        ->  connectButton_Component;

    object 
        ->  GetMainWindowObjects()
        ->  disconnectButton_Component
        ->  UseConnectButton(connectButton)
        ->  SetupDisconnectButton(toolkit, window);
}