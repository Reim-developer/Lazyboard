#include "Include/HotReload_Language.hpp"
#include <QObject>

using ZClipboard::GUI::Hot_Reload::HotReloadLanguage;
using ZClipboard::GUI::Hot_Reload::HotReloadImpl;

HotReloadLanguage *HotReloadLanguage::StartBuild()  {
    #if !defined (_WIN32)
                    
        MAKE_SMART_PTR(HotReloadImpl, Impl);

    #else

        Impl = MakePtr<HotReloadImpl>();

    #endif

    return this;
}

HotReloadLanguage *HotReloadLanguage::WhenDone() {
    return this;
}

void HotReloadLanguage::ThenAddListener(Func<void()> Function) {
    
    auto windowContext = this
        ->  Impl
        .   get()
        ->  windowContext;

    QObject::connect(&LanguageManager::GetLanguageManager(), &LanguageManager::OnLanguageChanged, windowContext, Function);
}

