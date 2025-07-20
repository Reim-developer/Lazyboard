#ifndef COMPONENTS_TOOLKIT_HPP
#define COMPONENTS_TOOLKIT_HPP
#include "../../../Utils/Include/Namespace_Macro.hpp"
#include "../../../Lib_Memory/Include/Memory.hpp"
#include "../../../Utils/Include/Utils.hpp"
#include "../../../GUI/Include/TableModel.hpp"
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QSystemTrayIcon>
#include <QMenu>

using ZClipboard::AppUtils::Utils;
using ZClipboard::GUI::TableModel;
using ZClipboard::Lib_Memory::PtrUnique;

GUI_TOOLKIT_NAMESPACE

    class ComponentsToolkit {
        private:
            PtrUnique<QTableView> ClipboardTableView;
            PtrUnique<TableModel> ModelTable;
            PtrUnique<QLineEdit> SearchArea;
            PtrUnique<QPushButton> ClearButton;
            PtrUnique<QPushButton> ConnectButton;
            PtrUnique<QPushButton> DisconnectButton;
            PtrUnique<QPushButton> SettingButton;
            PtrUnique<QSystemTrayIcon> SystemTrayIcon;
            PtrUnique<QMenu> SystemTrayMenu;

        public:
            QTableView *GetTableView();
            TableModel *GetTableModel();
            QLineEdit *GetSearchArea();
            QPushButton *GetClearButton();
            QPushButton *GetConnectButton();
            QPushButton *GetDisconnectButton();
            QPushButton *GetSettingButton();
            QSystemTrayIcon *GetSystemTrayIcon();
            QMenu *GetSystemTrayMenu();
    };

END_NAMESPACE

#endif // COMPONENTS_TOOLKIT_HPP