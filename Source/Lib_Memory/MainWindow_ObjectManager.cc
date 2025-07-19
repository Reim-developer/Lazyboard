#include "Include/MainWindow_ObjectManager.hpp"
#include "../Utils/Include/Utils.hpp"

#if defined (Z_DEBUG)
    #include "../Utils/Include/AssertNullPtr.hpp"
    #include "../Utils/Include/Logging.hpp"
    using ZClipboard::AppUtils::LogContext;
#endif 

using ZClipboard::Lib_Memory::MainWindowObjectManager;
using ZClipboard::Lib_Memory::MainWindowObjectData;
using ZClipboard::AppUtils::Utils;

using Self = MainWindowObjectManager;
using Object = MainWindowObjectData;

Object *Self::SetupObjectData() {
    if(!object) {
        Utils::MakeSmartPtr<Object>(object);
    }

    auto tableView_Raw = this->SetupFieldData<TableView>(tableView);
    auto clearButton_Raw = this->SetupFieldData<ClearButton>(clearButton);
    auto searchArea_Raw = this->SetupFieldData<SearchArea>(searchArea);
    auto notification_Raw = this->SetupFieldData<NotificationCore>(notificationCore);
    auto systemTray_Raw = this->SetupFieldData<SystemTray>(systemTray);
    auto disconnectButton_Raw = this->SetupFieldData<DisconnectButton>(disconnectButton);
    auto connectButton_Raw = this->SetupFieldData<ConnectButton>(connectButton);

    object->tableView_Component = tableView_Raw;
    object->clearButton_Component = clearButton_Raw;
    object->searchArea_Component = searchArea_Raw;
    object->notificationCore_Component = notification_Raw;
    object->systemTray_Component = systemTray_Raw;
    object->disconnectButton_Component = disconnectButton_Raw;
    object->connectButton_Component = connectButton_Raw;

    #if defined(Z_DEBUG)
        AssertContext{}.RequireNonNullPtr(tableView_Raw);
        AssertContext{}.RequireNonNullPtr(object->tableView_Component);
        AssertContext{}.RequireNonNullPtr(object.get());
        AssertContext{}.RequireNonNullPtr(object->notificationCore_Component);
        AssertContext{}.RequireNonNullPtr(object->systemTray_Component);
        AssertContext{}.RequireNonNullPtr(object->disconnectButton_Component);
        AssertContext{}.RequireNonNullPtr(object->connectButton_Component);

        LogContext{}.LogDebug(&tableView_Raw);
        LogContext{}.LogDebug(&object->tableView_Component);
        LogContext{}.LogDebug(object.get());
        LogContext{}.LogDebug(&object->notificationCore_Component);
        LogContext{}.LogDebug(&object->systemTray_Component);
        LogContext{}.LogDebug(&object->disconnectButton_Component);
        LogContext{}.LogDebug(&object->connectButton_Component);
    #endif

    return object.get();
}

Object *Self::InitiationObjects() {
    auto object = SetupObjectData();

    return object;
}

Object *Self::GetMainWindowObjects() {
    if(!object) {
        auto object = SetupObjectData();

        return object;
    }

    return object.get();
}