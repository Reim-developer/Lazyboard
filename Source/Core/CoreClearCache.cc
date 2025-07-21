#include "Include/CoreClearCache.hpp"
#include "../Utils/Include/Utils.hpp"

using ZClipboard::Core::CoreClearBuilder;
using ZClipboard::Core::CoreClearBuilderData;
using ZClipboard::Listener::ListenerCacheImpl;
using ZClipboard::AppUtils::Utils;

using Self = CoreClearBuilder;
using ImplData = CoreClearBuilderData;
using Button = QPushButton;
using Settings = QSettings;

#if defined(Z_DEBUG)
    #include "../Utils/Include/AssertNullPtr.hpp"
    #include "../Utils/Include/Logging.hpp"
#endif

Self *Self::StartBuild() {
    if(!Impl) {
        Impl = MakePtr<CoreClearBuilderData>();
    }
    
    return this;
}

Self *Self::WhenDone() {
    if(!func_Builder) {
        Utils::MakeSmartPtr<Listener>(func_Builder);
    }

    return this;
}

inline Button *Self::GetClearButton() noexcept {
    return this
        ->  Impl
        ->  button;
}

inline Settings *Self::GetSettings() noexcept {
    return this
        ->  Impl
        ->  settings;
}

inline TableView *Self::GetTableView() noexcept {
    return this 
        ->  Impl
        ->  tableView;
}

void Self::Finally_Setup_Listener() {
    auto clearButton = this->GetClearButton();
    auto settings = this->GetSettings();
    auto tableView = this->GetTableView();

    using ImplData = ListenerCacheImpl;
    const auto Function = func_Builder
        ->  StartBuild()
        ->  WithAndThen(&ImplData::button, clearButton)
        ->  WithAndThen(&ImplData::settings, settings)
        ->  WithAndThen(&ImplData::table, tableView)
        ->  WhenDone()
        ->  TryGetListener();

   
    #if defined(Z_DEBUG)
        using Assert = AssertContext;
        using Debug = LogContext;
        
        Assert{}.RequireNonNullPtr(Impl.get());
        Assert{}.RequireNonNullPtr(Impl->button);
        Assert{}.RequireNonNullPtr(func_Builder.get());
        Assert{}.RequireNonNullPtr(clearButton);
        Assert{}.RequireNonNullPtr(settings);
        Assert{}.RequireNonNullPtr(tableView);

        Debug{}.LogDebug(&Impl);
        Debug{}.LogDebug(&Impl->button);
        Debug{}.LogDebug(&Impl->tableView);
        Debug{}.LogDebug(&Impl->settings);
        Debug{}.LogDebug(&func_Builder);
    #endif

    QObject::connect(clearButton, &QPushButton::clicked, Function);
}
