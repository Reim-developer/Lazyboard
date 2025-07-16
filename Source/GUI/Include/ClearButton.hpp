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

#if defined (Z_DEBUG)
    #include "../../Utils/Include/Logging.hpp"
    using ZClipboard::AppUtils::LogContext;
#endif

using ZClipboard::GUI::TableView;
using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::Core::ClearCoreBuilder;
using ZClipboard::Listener::ClearCacheListener;

GUI_NAMESPACE

    class ClearButton  {
        private:
            ClearCoreBuilder BuilderCore;
            ClearCacheListener BuilderFunc;

        public:
            void SetupClearButton(QGridLayout *layout, TableView* tableView);
            QPushButton *getClearButton();

        private:
            void SetupEventListener(TableView *tableView);
        
        private:
            PtrUnique<QSettings> settings;
            PtrUnique<QPushButton> clearButton;

        #if defined (Z_DEBUG)
            private:
                void __LOGGING_ALL_OBJECTS__() {
                    LogContext{}.LogDebug(&BuilderCore);
                    LogContext{}.LogDebug(&BuilderFunc);
                    LogContext{}.LogDebug(&settings);
                    LogContext{}.LogDebug(&clearButton);
                }

        #endif
    };

END_NAMESPACE

#endif  // CLEAR_BUTTON_HPP