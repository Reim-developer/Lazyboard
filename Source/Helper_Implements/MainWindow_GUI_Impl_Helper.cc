#include "Include/MainWindow_GUI_Impl_Helper.hpp"

using ZClipboard::GUI::SearchAreaImpl;
using Impl = SearchAreaImpl;
using Window = QMainWindow;

void ClearButtonComponentImpl(Object *object, ComponentsManager *componentsManager) {
    auto tableView = object
        ->  GetMainWindowObjects()
        ->  tableView_Component;

    object
        ->  GetMainWindowObjects()
        ->  clearButton_Component
        ->  SetupClearButton(componentsManager, tableView);
}

void TableViewComponentImpl(Object *object, ComponentsManager *componentsManager) {
    auto tableView = object
        ->  GetMainWindowObjects()
        ->  tableView_Component;

    tableView
        ->  UseToolkit(componentsManager)
        ->  SetupTableView();
}

void SearchAreaComponentImpl(Object *object, ComponentsManager *componentsManager) {
    auto tableView = object
        ->  GetMainWindowObjects()
        ->  tableView_Component;

    object
        ->  GetMainWindowObjects()
        ->  searchArea_Component
        ->  StartBuild()
        ->  WithAndThen(&Impl::tableView, tableView)
        ->  WithAndThen(&Impl::componentsManager, componentsManager)
        ->  WhenDone()
        ->  SetupSearchPanel();
}

void NotificationComponentImpl(Object *object, ComponentsManager *componentsManager) {
    auto systemTrayIcon = componentsManager->GetSystemTrayIcon();
    
    auto clipboard = object
        ->  GetMainWindowObjects()
        ->  tableView_Component
        ->  GetClipboard();

    object
        ->  GetMainWindowObjects()
        ->  notificationCore_Component
        ->  onClipboardChanged(systemTrayIcon, clipboard);
}

void SystemTrayComponentImpl(
        Window *window, Object *object, 
        ComponentsManager *componentsManager, QIcon appIcon) {

    object
        ->  GetMainWindowObjects()
        ->  systemTray_Component
        ->  SetupSystemTray(window, &appIcon, componentsManager);
}

void ConnectButtonComponentImpl(Window *window, Object *object, ComponentsManager *componentsManager) {
    object
        ->  GetMainWindowObjects()
        ->  connectButton_Component
        ->  SetupConnectButton(window, componentsManager);
}

void DisconnectButtonComponentImpl(
        Window *window, 
        Object *object, ComponentsManager *componentsManager) {

    auto connectButton = object
        ->  GetMainWindowObjects()
        ->  connectButton_Component;

    object 
        ->  GetMainWindowObjects()
        ->  disconnectButton_Component
        ->  UseConnectButton(connectButton)
        ->  SetupDisconnectButton(componentsManager, window);
}

void SettingButtonComponentImpl(
        Window *window, 
        Object *object, ComponentsManager *componentsManager) {
            
    object
        ->  GetMainWindowObjects()
        ->  settingButton_Component
        ->  SetupSettingButton(window, componentsManager);
}