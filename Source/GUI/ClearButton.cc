#include "Include/ClearButton.hpp"
#include <QGridLayout>
#include <QPushButton>
#include "../Utils/Include/Config.hpp"
#include "../Lib_Memory/Include/Memory.hpp"
#include "../Listener/Include/ListenerClearCache.hpp"
#include <QSettings>
#include "../Core/Include/CoreClearCache.hpp"
#include "Include/TableView.hpp"
#include "../Utils/Include/Meta_Macro.hpp"
#include "../Utils/Include/Utils.hpp"
#include "Toolkit/Include/Layout_Tookit.hpp"

using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::GUI::ClearButton;
using ZClipboard::Listener::ListenerCacheImpl;
using ZClipboard::AppUtils::Utils;
using ZClipboard::GUI::Toolkit::WidgetProperty;
using ZClipboard::GUI::Toolkit::GridLayoutAdd;

void ClearButton::SetupClearButton(QGridLayout *layout, TableView* tableView) {
    Utils::MakeSmartPtr<QPushButton>(clearButton);
    Utils::MakeSmartPtr<QSettings>(settings, AUTHOR_NAME, APP_NAME);
    
    using WgImpl = WidgetProperty;
    GridLayoutAdd(layout, WgImpl{
        .widget = clearButton.get(),
        .row = 0, .column = 2
    });

    SetupEventListener(tableView);
    #if defined (Z_DEBUG)
        __LOG__
    #endif
}

void ClearButton::SetupEventListener(TableView *tableView) {
    using Impl = ListenerCacheImpl;
    const auto Function = BuilderFunc
                .   StartBuild()
                    ->  WithAndThen(&Impl::button, clearButton.get())
                    ->  WithAndThen(&Impl::settings, settings.get())
                    ->  WithAndThen(&Impl::table, tableView)
                    ->  WhenDone()
                    ->  TryGetListener();

    BuilderCore
        .   StartBuild(clearButton.get())
            ->  ThenAddListener(Function);
}

QPushButton *ClearButton::getClearButton() {
    return clearButton.get();
}