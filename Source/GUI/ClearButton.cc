#include "Include/ClearButton.hpp"
#include <QGridLayout>
#include <QPushButton>
#include "../Utils/Include/Config.hpp"
#include "../Lib_Memory/Include/Memory.hpp"
#include "../Listener/Include/ListenerClearCache.hpp"
#include <QSettings>
#include "../Core/Include/CoreClearCache.hpp"
#include "Include/TableView.hpp"

using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::Lib_Memory::MakePtr;
using ZClipboard::GUI::ClearButton;
using ZClipboard::Listener::ListenerCache;

void ClearButton::SetupClearButton(QGridLayout *layout, TableView* tableView) {
    clearButton = MakePtr<QPushButton>();
    settings = MakePtr<QSettings>(AUTHOR_NAME, APP_NAME);
    layout->addWidget(clearButton.get(), 0, 2);

    const auto Function = BuilderFunc
                .StartBuild()
                    ->  WithAndThen(&ListenerCache::button, clearButton.get())
                    ->  WithAndThen(&ListenerCache::settings, settings.get())
                    ->  WithAndThen(&ListenerCache::table, tableView)
                    ->  TryGetListener();

    BuilderCore
        .   StartBuild(clearButton.get())
        ->  ThenAddListener(Function);
}

QPushButton *ClearButton::getClearButton() {
    return clearButton.get();
}