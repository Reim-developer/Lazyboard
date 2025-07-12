#ifndef CLEAR_CACHE_LISTENER_HPP
#define CLEAR_CACHE_LISTENER_HPP
#include <QSettings>
#include <QPushButton>
#include "../../GUI/Include/TableView.hpp"
#include "../../Lib_Memory/Include/Memory.hpp"
#include "../../Utils/Include/Meta_Macro.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"

using std::function;
using ZClipboard::Lib_Memory::MakePtr;
using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::GUI::TableView;

LISTENER_NAMESPACE
    struct ListenerCache {  
        TableView *table;
        QSettings *settings;
        QPushButton *button;
    };

    class ClearCacheListener {
        private:
            PtrUnique<ListenerCache> cache;
            
            public:
            ClearCacheListener *StartBuild();

            CLASS_BUILD(T, V)
            ClearCacheListener *WithAndThen(T ListenerCache::*member, V &&value) {
                cache.get()->*member = FORWARD(T, value);

                return this;
            }

            function<void()> TryGetListener();
    };


END_NAMESPACE
#endif