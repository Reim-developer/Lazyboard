#include "Include/CoreSettingWindow.hpp"
#include "../Utils/Include/Utils.hpp"

using ZClipboard::Core::CoreSettingWindow;
using ZClipboard::Core::CoreSettingWindowData;
using ZClipboard::GUI::Toolkit::SettingWindowLayoutData;
using ZClipboard::AppUtils::Utils;

using Self = CoreSettingWindow;
using DataImpl = CoreSettingWindowData;
using LayoutManager = SettingWindowLayoutManager;
using WindowComponents = SettingWindowComponentsManager;
using Window = QMainWindow;
using Button = QPushButton;
using Layout = QGridLayout;

#if defined (Z_DEBUG)
    #include "../Utils/Include/AssertNullPtr.hpp"
    #include "../Utils/Include/Logging.hpp"

    using ZClipboard::AppUtils::LogContext;

    using Log = LogContext;
    using Assert = AssertContext;
#endif 

Self *Self::StartBuild() noexcept {
    Utils::MakeSmartPtr<DataImpl>(Impl);

    return this;
}


Layout *Self::GetLayout() noexcept {
    return this 
        ->  Impl
        ->  layout;
}

Self *Self::WithLayout(Layout *layout) {
    this
        ->  Impl
        ->  layout
        =   layout;

    return this;
}

Self *Self::WhenDone() noexcept {
    #if defined (Z_DEBUG)
        using Assert = AssertContext;
        using Log = LogContext;

        Assert{}.RequireNonNullPtr(Impl.get());

        Log{}.LogDebug(Impl.get());
    #endif

    return this;
}

void Self::SetupWindow(WindowComponents *components) noexcept {
    auto layout = this->GetLayout();

    Utils::MakeSmartPtr<LayoutManager>(layoutManager);
        
    #if defined (Z_DEBUG)
        Assert{}.RequireNonNullPtr(layoutManager.get());
        Assert{}.RequireNonNullPtr(components);
        Assert{}.RequireNonNullPtr(layout);
    #endif
    
    using Impl = SettingWindowLayoutData;
    layoutManager
        ->  StartBuild()
        ->  WithAndThen(&Impl::componentsManager, components)
        ->  WithAndThen(&Impl::layout, layout)
        ->  WhenDone()
        ->  SetupSettingWindowLayout();
}