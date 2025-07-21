#ifndef CORE_CLEAR_HPP
#define CORE_CLEAR_HPP
#include <QObject>
#include <QPushButton>
#include <QSettings>
#include "../../GUI/Include/TableView.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../../Lib_Memory/Include/Memory.hpp"
#include "../../Utils/Include/Meta_Macro.hpp"
#include "../../Listener/Include/ListenerClearCache.hpp"
#include "../../Utils/Include/Meta_Macro.hpp"

using std::function;
using ZClipboard::Lib_Memory::MakePtr;
using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::GUI::TableView;
using ZClipboard::Listener::ClearCacheListener;
using std::enable_if_t;
using std::is_invocable_v;

CORE_NAMESPACE

    struct CoreClearBuilderData {
        QPushButton *button;
        QSettings *settings;
        TableView *tableView;
    };

    class CoreClearBuilder {
        private:
            using Self = CoreClearBuilder;
            using ImplData = CoreClearBuilderData;
            using Listener = ClearCacheListener;
            using Button = QPushButton;
            using Settings = QSettings;
            
        private:
            PtrUnique<ImplData> Impl;
            PtrUnique<Listener> func_Builder;
    

        private:
            inline Button *GetClearButton() noexcept;
            inline Settings *GetSettings() noexcept;
            inline TableView *GetTableView() noexcept;

        public:
            Self *StartBuild();

            CLASS_BUILD(T, V)
            Self *WithAndThen(T ImplData::*member, V&& value) {
                Impl.get()->*member = FORWARD(V, value);

                return this;
            }

            Self *WhenDone();
            void Finally_Setup_Listener();
            
    };

END_NAMESPACE
#endif  // CORE_CLEAR_HPP