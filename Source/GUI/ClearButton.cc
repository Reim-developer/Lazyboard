#include "Include/ClearButton.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Listener/Include/ListenerClearCache.hpp"
#include "../Core/Include/CoreClearCache.hpp"
#include "Include/TableView.hpp"
#include "../Utils/Include/Utils.hpp"

using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::GUI::ClearButton;
using ZClipboard::Listener::ListenerCacheImpl;
using ZClipboard::AppUtils::Utils;

void ClearButton::SetupClearButton(Toolkit *toolkit, TableView *tableView) {
    auto clearButton = toolkit->GetClearButton();
    Utils::MakeSmartPtr<QSettings>(settings, AUTHOR_NAME, APP_NAME);
    
    SetupEventListener(clearButton, tableView);
    #if defined (Z_DEBUG)
        __LOGGING_ALL_OBJECTS__(clearButton);
    #endif
}

void ClearButton::SetupEventListener(QPushButton *clearButton, TableView *tableView) {
    using Impl = ListenerCacheImpl;

    const auto Function = BuilderFunc
                .   StartBuild()
                    ->  WithAndThen(&Impl::button, clearButton)
                    ->  WithAndThen(&Impl::settings, settings.get())
                    ->  WithAndThen(&Impl::table, tableView)
                    ->  WhenDone()
                    ->  TryGetListener();

    BuilderCore
        .   StartBuild(clearButton)
            ->  ThenAddListener(Function);
}
