#ifndef LAYOUT_MANAGER_TOOLKIT_HPP
#define LAYOUT_MANAGER_TOOLKIT_HPP
#include "../../../Utils/Include/Namespace_Macro.hpp"
#include "../../../Lib_Memory/Include/Memory.hpp"
#include "../../../Utils/Include/Meta_Macro.hpp"
#include "Components_Toolkit.hpp"
#include "Layout_Tookit.hpp"
#include <QGridLayout>

using ZClipboard::GUI::Toolkit::ComponentsToolkit;
using ZClipboard::Lib_Memory::PtrUnique;

#if defined (Z_DEBUG)
    #include "../../../Utils/Include/Logging.hpp"
    using ZClipboard::AppUtils::LogContext;
#endif

GUI_TOOLKIT_NAMESPACE

    struct LayoutMangerTookitData {
        QGridLayout *layout;
        ComponentsToolkit *tookit;
    };

    class LayoutMangerTookit {
        private:
            using Self = LayoutMangerTookit;
            using ImplData = LayoutMangerTookitData;
            using Toolkit  = ComponentsToolkit;
            using Widget = WidgetProperty;

        private:
            PtrUnique<ImplData> Impl;
            QGridLayout *GetGridLayout();
            Toolkit *GetTookit();

        /*
        * Application widget layout data.
        */
        private:
            Widget GetTableViewLayout(Toolkit *tookit); 
            Widget GetSearchAreaLayout(Toolkit *tookit);
            Widget GetConnectButtonLayout(Toolkit *toolkit);
            Widget GetDisconnectButtonLayout(Toolkit *toolkit);

        public:
            Self *StartBuild();

            CLASS_BUILD(T, V)
            Self *WithAndThen(T ImplData::*member, V &&value) {
                Impl.get()->*member = FORWARD(V, value);

                return this;
            }

            Self *WhenDone();

            void SetupAppGridLayout();
        
        #if defined (Z_DEBUG)
            private:
                void __LOGGING_ALL_OBJECTS__() {
                    LogContext{}.LogDebug(&Impl->layout);
                    LogContext{}.LogDebug(&Impl->layout);
                }
        #endif
    };

END_NAMESPACE
#endif // LAYOUT_MANAGER_TOOLKIT_HPP