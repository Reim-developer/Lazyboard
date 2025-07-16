#ifndef THEME_IMPL_HELPER_HPP
#define THEME_IMPL_HELPER_HPP
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../../Lib_Memory/Include/Memory.hpp"
#include "../../Preload/Include/PreloadTheme.hpp"
#include "../../Utils/Include/Meta_Macro.hpp"
#include "../../Utils/Include/Utils.hpp"

using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::Preload::PreloadTheme;
using ZClipboard::AppUtils::Utils;

HELPER_IMPLEMENTS_NAMESPACE
    struct zClipboard_Helper {
        PreloadTheme *preloadTheme;
        QApplication *application;
    };    

    class Theme_Impl_Helper {
        private:
            PtrUnique<zClipboard_Helper> Impl;

        private:
            PreloadTheme *GetPreloadTheme() {
                return this
                    ->  Impl
                    ->  preloadTheme;
            }

            QApplication *GetQApplication() {
                return this
                    ->  Impl
                    ->  application;
            }

        private:
            using Implement = zClipboard_Helper;

        public:
            Theme_Impl_Helper *StartBuild();
            
            CLASS_BUILD(T, V)
            Theme_Impl_Helper *WithAndThen(T Implement::*member, V &&value) {
                Impl.get()->*member = FORWARD(T, value);

                return this;
            }

            Theme_Impl_Helper *WhenDone();

            void SetupTheme();
    };

END_NAMESPACE

#endif // THEME_IMPL_HELPER_HPP
