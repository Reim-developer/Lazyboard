#include "include/clearButton.hpp"
#include <QGridLayout>
#include <QPushButton>
#include <QVariant>
#include <QTimer>
#include "include/ztable.hpp"
#include "../zUtils/include/config.hpp"
#include "../lib_memory/include/memory.hpp"
#include "../listener/include/clearCacheListener.hpp"
#include <QSettings>
#include "../core/include/clear.hpp"

using zclipboard::lib_memory::PtrUnique;
using zclipboard::lib_memory::MakePtr;
using zclipboard::zGui::ClearButton;
using zclipboard::listener::ListenerCache;

void ClearButton::addClearButton(QGridLayout *layout, ZTable* table) {
    clearButton = MakePtr<QPushButton>();
    settings = MakePtr<QSettings>(AUTHOR_NAME, APP_NAME);
    layout->addWidget(clearButton.get(), 0, 2);

    const auto Function = BuilderFunc
                .StartBuild()
                    ->  WithAndThen(&ListenerCache::button, clearButton.get())
                    ->  WithAndThen(&ListenerCache::settings, settings.get())
                    ->  WithAndThen(&ListenerCache::table, table)
                    ->  TryGetListener();

    BuilderCore
        .StartBuild(clearButton.get())
            ->  ThenAddListener(Function);
}

QPushButton *ClearButton::getClearButton() {
    return clearButton.get();
}