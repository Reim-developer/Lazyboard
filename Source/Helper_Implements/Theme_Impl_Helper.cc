#include "Include/Theme_Impl_Helper.hpp"

using ZClipboard::Helper_Implements::Theme_Impl_Helper;

#define __SELF__ Theme_Impl_Helper

__SELF__ * __SELF__::StartBuild() {
    if(!Impl) {
        Utils::MakeSmartPtr<Implement>(Impl);
    }

    return this;
} 

__SELF__ *__SELF__::WhenDone() {
    return this;
}

void __SELF__::SetupTheme() {
    const auto Preload = this->GetPreloadTheme();
    const auto App = this->GetQApplication();

    const auto IS_DEFAULT_THEME = Preload->LoadDefaultTheme();

    if(!IS_DEFAULT_THEME) {
        Preload->LoadSettingTheme(*App);
    }

    Preload->OnSettingThemeChanged(*App);
}
