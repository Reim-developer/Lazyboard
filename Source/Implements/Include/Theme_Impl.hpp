#ifndef THEME_IMPL_HPP
#define THEME_IMPL_HPP
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../../Utils/Include/Utils.hpp"
#include "../../Helper_Implements/Include/Theme_Impl_Helper.hpp"
#include "../../Preload/Include/PreloadTheme.hpp"
#include "../../Utils/Include/Utils.hpp"

using ZClipboard::AppUtils::Utils;
using ZClipboard::Helper_Implements::Theme_Impl_Helper;
using ZClipboard::AppUtils::Utils;
using ZClipboard::Preload::PreloadTheme;

#if defined (Z_DEBUG)
    #include "../../Utils/Include/Logging.hpp"
    using ZClipboard::AppUtils::LogContext;
#endif

IMPLEMENTS_NAMESPACE

    class Theme_Impl {
        private:
            using Self =  Theme_Impl;
            using Impl = Theme_Impl_Helper;
            PtrUnique<Impl> zClipboard_Impl;
            PtrUnique<PreloadTheme> preloadTheme;

        public:
            Self *StartBuild();
            void ThemeImplement(QApplication *application);
        
        #if defined (Z_DEBUG)
            private:
                void __LOGGING_ALL_OBJECTS__() {
                    LogContext{}.LogDebug(&zClipboard_Impl);
                    LogContext{}.LogDebug(&preloadTheme);
                }
        #endif
    };

END_NAMESPACE

#endif // THEME_IMPL_HPP