#ifndef CLEAR_CACHE_LISTENER_HPP
#define CLEAR_CACHE_LISTENER_HPP
#include <QSettings>
#include <QPushButton>
#include "../../GUI/Include/TableView.hpp"
#include "../../Lib_Memory/Include/Memory.hpp"
#include "../../Utils/Include/Meta_Macro.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../../Utils/Include/Utils.hpp"

using std::function;
using ZClipboard::Lib_Memory::MakePtr;
using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::GUI::TableView;
using ZClipboard::AppUtils::Utils;

LISTENER_NAMESPACE
    struct ListenerCacheImpl {  
        TableView *table;
        QSettings *settings;
        QPushButton *button;
    };

    class ClearCacheListener {
        private:
            using Self = ClearCacheListener;

        private:
            PtrUnique<ListenerCacheImpl> Impl;
            
        public:
            Self *StartBuild() {
                Utils::MakeSmartPtr<ListenerCacheImpl>(Impl);
                    
                return this;
            }

            CLASS_BUILD(T, V)
            ClearCacheListener *WithAndThen(T ListenerCacheImpl::*member, V &&value) {
                Impl.get()->*member = FORWARD(T, value);

                return this;
            }


            Self *WhenDone() {
                return this;
            }

            VOID_FUNC TryGetListener();
    };


END_NAMESPACE
#endif