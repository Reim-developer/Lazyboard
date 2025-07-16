#include "Include/Theme_Impl.hpp"

using ZClipboard::Implements::Theme_Impl;
using ZClipboard::Helper_Implements::zClipboard_Helper;

#define __SELF__ Theme_Impl

__SELF__ *__SELF__::StartBuild() {
    if(!zClipboard_Impl) {
        Utils::MakeSmartPtr<Z_Impl>(zClipboard_Impl);
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
    #define __IMPL__ zClipboard_Helper

    zClipboard_Impl
        ->  StartBuild()
        ->  WithAndThen(&__IMPL__::preloadTheme, preloadTheme.get())
        ->  WithAndThen(&__IMPL__::application, application)
        ->  WhenDone()
        ->  SetupTheme(); 
}