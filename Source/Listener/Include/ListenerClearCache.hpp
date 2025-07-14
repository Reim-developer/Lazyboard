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
    struct ListenerCacheImpl {  
        TableView *table;
        QSettings *settings;
        QPushButton *button;
    };

    class ClearCacheListener {
        private:
            PtrUnique<ListenerCacheImpl> Impl;
            
            public:
                ClearCacheListener *StartBuild() {
                    #if !defined (_WIN32)

                        MAKE_SMART_PTR(ListenerCacheImpl, Impl);

                    #else

                        Impl = MakePtr<ListenerCacheImpl>();

                    #endif

                    return this;
                }

                CLASS_BUILD(T, V)
                ClearCacheListener *WithAndThen(T ListenerCacheImpl::*member, V &&value) {
                    Impl.get()->*member = FORWARD(T, value);

                    return this;
                }

                ClearCacheListener *WhenDone() {
                    return this;
                }

                VOID_FUNC TryGetListener();
    };


END_NAMESPACE
#endif