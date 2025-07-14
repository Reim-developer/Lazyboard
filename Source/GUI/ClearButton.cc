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

using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::Lib_Memory::MakePtr;
using ZClipboard::GUI::ClearButton;
using ZClipboard::Listener::ListenerCacheImpl;

void ClearButton::SetupClearButton(QGridLayout *layout, TableView* tableView) {
    #if !defined(_WIN32)

        MAKE_SMART_PTR(QPushButton, clearButton);
        MAKE_SMART_PTR(QSettings, settings, (AUTHOR_NAME, APP_NAME));
        ADD_LAYOUT_TO(layout, clearButton.get(), 0, 2);

    #else

        clearButton = MakePtr<QPushButton>();
        settings = MakePtr<QSettings>(AUTHOR_NAME, APP_NAME);
        layout->addWidget(clearButton.get(), 0, 2);

    #endif 

   
    using Impl = ListenerCacheImpl;
    const auto Function = BuilderFunc
                .StartBuild()
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