#include "Include/Theme_Impl.hpp"

using ZClipboard::Implements::Theme_Impl;
using ZClipboard::Helper_Implements::Theme_Impl_Data;

#define __SELF__ Theme_Impl

__SELF__ *__SELF__::StartBuild() {
    if(!zClipboard_Impl) {
        Utils::MakeSmartPtr<Impl>(zClipboard_Impl);
    }

    if(!preloadTheme) {
        Utils::MakeSmartPtr<PreloadTheme>(preloadTheme);
    }

    #if defined (Z_DEBUG)
        __LOG__
    #endif
    return this;
}

void __SELF__::ThemeImplement(QApplication *application) {
    #define __IMPL__ Theme_Impl_Data

    zClipboard_Impl
        ->  StartBuild()
        ->  WithAndThen(&__IMPL__::preloadTheme, preloadTheme.get())
        ->  WithAndThen(&__IMPL__::application, application)
        ->  WhenDone()
        ->  SetupTheme(); 
}