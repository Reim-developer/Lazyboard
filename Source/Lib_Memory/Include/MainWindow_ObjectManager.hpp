#ifndef MainWindow_ObjectManager
#define MainWindow_ObjectManager
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../../GUI/Include/TableView.hpp"
#include "../../GUI/Include/ClearButton.hpp"
#include "../../GUI/Include/SearchPanel.hpp"
#include "../../GUI/Include/SystemTray.hpp"
#include "../../GUI/Include/DisconnectButton.hpp"
#include "../../GUI/Include/GetConnectButton.hpp"
#include "../../Core/Include/CoreNotification.hpp"
#include "Memory.hpp"
#include <utility>

using ZClipboard::Lib_Memory::MakePtr;
using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::GUI::TableView;
using ZClipboard::GUI::ClearButton;
using ZClipboard::GUI::SearchArea;
using ZClipboard::GUI::SystemTray;
using ZClipboard::GUI::ConnectButton;
using ZClipboard::GUI::DisconnectButton;
using ZClipboard::Core::NotificationCore;

LIB_MEMORY_NAMESPACE
    struct MainWindowObjectData {
        TableView *tableView_Component;
        ClearButton *clearButton_Component;
        SearchArea *searchArea_Component;
        NotificationCore *notificationCore_Component;
        SystemTray *systemTray_Component;
        ConnectButton *connectButton_Component;
        DisconnectButton *disconnectButton_Component;
    };

    class MainWindowObjectManager {
        private:
            using Object = MainWindowObjectData;

        private:
            PtrUnique<Object> object;
            PtrUnique<TableView> tableView;
            PtrUnique<ClearButton> clearButton;
            PtrUnique<SearchArea> searchArea;
            PtrUnique<NotificationCore> notificationCore;
            PtrUnique<SystemTray> systemTray;
            PtrUnique<DisconnectButton> disconnectButton;
            PtrUnique<ConnectButton> connectButton;

        private:
            Object *SetupObjectData();
            
            template<typename T, typename V, typename... Args>
            T *SetupFieldData(V&& valueName, Args&&... args) {
                if(valueName == nullptr) {
                    Utils::MakeSmartPtr<T>(std::forward<V>(valueName), std::forward<Args>(args)...);
                }

                return valueName.get();
            }

        public:
            /*
            * Initiation all objects of `MainWindow`
            * 
            * Then, it will return `MainWindowObjectData`
            * struct data, and you can access this
            * structure fields field, safely.
            */
            Object *InitiationObjects();

            /*
            * Get `MainWindowObject`, if can.
            */
            Object *GetMainWindowObjects();
    };

END_NAMESPACE

#endif // MainWindow_ObjectManager