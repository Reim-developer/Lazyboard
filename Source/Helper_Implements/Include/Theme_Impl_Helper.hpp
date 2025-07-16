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
    struct Theme_Impl_Data {
        PreloadTheme *preloadTheme;
        QApplication *application;
    };    

    class Theme_Impl_Helper {
        private:
            PtrUnique<Theme_Impl_Data> Impl;

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
            using Implement = Theme_Impl_Data;
            using Self = Theme_Impl_Helper;

        public:
            Self *StartBuild();
            
            CLASS_BUILD(T, V)
            Self *WithAndThen(T Implement::*member, V &&value) {
                Impl.get()->*member = FORWARD(T, value);

                return this;
            }

            Self *WhenDone();
            void SetupTheme();
    };

END_NAMESPACE

#endif // THEME_IMPL_HELPER_HPP
