#ifndef CLEAR_BUTTON_HPP
#define CLEAR_BUTTON_HPP

#include <QGridLayout>
#include <QPushButton>
#include <QObject>
#include "TableView.hpp"
#include <QSettings>
#include "../../Lib_Memory/Include/Memory.hpp"
#include "../../Core/Include/CoreClearCache.hpp"
#include "../../Listener/Include/ListenerClearCache.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../Toolkit/Include/MainWindow_Components.hpp"

#if defined (Z_DEBUG)
    #include "../../Utils/Include/Logging.hpp"
    using ZClipboard::AppUtils::LogContext;
#endif

using ZClipboard::GUI::TableView;
using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::Core::ClearCoreBuilder;
using ZClipboard::Listener::ClearCacheListener;
using ZClipboard::GUI::Toolkit::ComponentsToolkit;

GUI_NAMESPACE

    class ClearButton  {
        private:
            ClearCoreBuilder BuilderCore;
            ClearCacheListener BuilderFunc;
        
        private:
            using Toolkit = ComponentsToolkit;

        public:
            void SetupClearButton(Toolkit *toolkit, TableView *tableView);
            
        private:
            void SetupEventListener(QPushButton *clearButton, TableView *tableView);
        
        private:
            PtrUnique<QSettings> settings;

        #if defined (Z_DEBUG)
            private:
                void __LOGGING_ALL_OBJECTS__(QPushButton *clearButton) {
                    LogContext{}.LogDebug(&BuilderCore);
                    LogContext{}.LogDebug(&BuilderFunc);
                    LogContext{}.LogDebug(&settings);
                    LogContext{}.LogDebug(&clearButton);
                }

        #endif
    };

END_NAMESPACE

#endif  // CLEAR_BUTTON_HPP