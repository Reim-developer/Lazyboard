#ifndef CLEAR_CACHE_LISTENER_HPP
#define CLEAR_CACHE_LISTENER_HPP
#include <QSettings>
#include <QPushButton>
#include "../../zGui/include/ztable.hpp"
#include "../../lib_memory/include/memory.hpp"
#include <functional>
#include <utility>

using std::function;
using zclipboard::lib_memory::MakePtr;
using zclipboard::lib_memory::PtrUnique;
using zclipboard::zGui::ZTable;

namespace zclipboard::listener {
    struct ListenerCache {  
        ZTable *table;
        QSettings *settings;
        QPushButton *button;
    };

    class ClearCacheListener {
        private:
            PtrUnique<ListenerCache> cache;
            
            public:
            ClearCacheListener *StartBuild();

            template<typename T, typename V>
            ClearCacheListener *WithAndThen(T ListenerCache::*member, V &&value) {
                cache.get()->*member = std::forward<V>(value);
                return this;
            }

            function<void()> TryGetListener();
    };

}  // namespace zclipboard::listener

#endif