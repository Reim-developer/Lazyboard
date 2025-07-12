#ifndef ZWINDOW_HPP
#define ZWINDOW_HPP
#include <QMainWindow>
#include <QIcon>
#include <QGridLayout>
#include <QWidget>
#include <QString>
#include <QSystemTrayIcon>
#include <QStringLiteral>
#include <QMenu>
#include "DisconnectButton.hpp"
#include "SearchPanel.hpp"
#include "ClearButton.hpp"
#include "GetConnectButton.hpp"
#include "SettingDialog.hpp"
#include "SystemTray.hpp"
#include "../../Core/Include/CoreNotification.hpp"
#include <QSettings>
#include "../../Lib_Memory/Include/Memory.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "TableView.hpp"

using ZClipboard::Core::NotificationCore;
using ZClipboard::GUI::DisconnectButton;
using ZClipboard::GUI::TableView;
using ZClipboard::GUI::ClearButton;
using ZClipboard::GUI::GetButton;
using ZClipboard::GUI::SearchArea;
using ZClipboard::GUI::SettingButton;
using ZClipboard::GUI::SystemTray;
using ZClipboard::Lib_Memory::PtrUnique;

GUI_NAMESPACE

    struct AppConfig {
        inline static constexpr int Z_WINDOW_WIDTH = 800;
        inline static constexpr int Z_WINDOW_HEIGHT = 600;
    };

    class AppMainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit AppMainWindow(QWidget *zWindow = nullptr);
        void loadTranslator();

    private:
        void setupGui();
        void createSystemTray();
        void addTrayMenuActions(QSystemTrayIcon *trayIcon);
        void translatorDectect();

    protected:
        void closeEvent(QCloseEvent *event) override;

    private slots:
        void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

    private:
        NotificationCore *notificationCore;

        QSettings *settings;
        QIcon appIcon;
        QWidget *centralWidget;
        QGridLayout *windowLayout;
        SystemTray *systemTray;

        PtrUnique<TableView> tableView;
        SearchArea *searchArea;

        ClearButton *clearButton;
        GetButton *getButton;
        SettingButton *settingButton;
        DisconnectButton *disconnectButton;
    };

END_NAMESPACE

#endif  // ZWINDOW_HPP