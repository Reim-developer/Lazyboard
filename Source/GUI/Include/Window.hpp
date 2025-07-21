#ifndef ZWINDOW_HPP
#define ZWINDOW_HPP
#include <QMainWindow>
#include <QIcon>
#include <QGridLayout>
#include <QWidget>
#include <QString>
#include "LanguageManager.hpp"
#include <QSettings>
#include "../../Lib_Memory/Include/Memory.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../Hot_Reload/Include/HotReload_Language.hpp"
#include "../Toolkit/Include/MainWindow_Components.hpp"
#include "../../Lib_Memory/Include/MainWindow_ObjectManager.hpp"
#include "../../Implements/GUI_Components/Include/Manager_MainWindow_Component_Impl.hpp"

#if defined (Z_DEBUG)
    #include "../../Utils/Include/Logging.hpp"
    using ZClipboard::AppUtils::LogContext;
#endif 

using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::GUI::Hot_Reload::HotReloadLanguage;
using ZClipboard::GUI::Hot_Reload::HotReloadImpl;
using ZClipboard::GUI::Toolkit::MainWindowComponentsManager;
using ZClipboard::AppUtils::Utils;
using ZClipboard::Lib_Memory::MainWindowObjectManager;
using ZClipboard::Implements::MainWindowComponentsImpl;


GUI_NAMESPACE

    struct AppConfig {
        inline static constexpr int WINDOW_WIDTH = 800;
        inline static constexpr int WINDOW_HEIGHT = 600;
    };

    class AppMainWindow : public QMainWindow {
        Q_OBJECT

    private:
        using Object = MainWindowObjectManager;
        using GUI_Manager = MainWindowComponentsImpl;

    public:
        explicit AppMainWindow(QWidget *zWindow = nullptr);
        void Translator();

    private:
        void InitiationObject();
        void SetupApplicationGUI();
        void SetupSystemTray();
        void addTrayMenuActions(QSystemTrayIcon *trayIcon);
        void translatorDectect();

    protected:
        void closeEvent(QCloseEvent *event) override;

    private slots:
        void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

    private:
        PtrUnique<Object> objectManager;
        PtrUnique<MainWindowComponentsManager> componentsManager;
        PtrUnique<HotReloadLanguage> hotReloadLanguage;
        PtrUnique<GUI_Manager> manager_GUI;

        QSettings *settings;
        QIcon appIcon;
        QWidget *centralWidget;
        QGridLayout *windowLayout;


        #if defined (Z_DEBUG)
            private:
                void __LOGGING_ALL_OBJECTS__() {
                    LogContext{}.LogDebug(&objectManager);
                    LogContext{}.LogDebug(&objectManager->GetMainWindowObjects()->tableView_Component);
                    LogContext{}.LogDebug(&objectManager->GetMainWindowObjects()->searchArea_Component);
                    LogContext{}.LogDebug(&objectManager->GetMainWindowObjects()->clearButton_Component);
                    LogContext{}.LogDebug(&objectManager->GetMainWindowObjects()->systemTray_Component);
                    LogContext{}.LogDebug(&hotReloadLanguage);
                }
        #endif
    };

END_NAMESPACE

#endif  // ZWINDOW_HPP