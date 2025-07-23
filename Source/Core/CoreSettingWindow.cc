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
#endif 

Self *Self::StartBuild() noexcept {
    if(!Impl) {
        Utils::MakeSmartPtr<DataImpl>(Impl);
    }

    return this;
}

WindowComponents *Self::GetWindowComponents() noexcept {
    if(!windowComponents) {
        Utils::MakeSmartPtr<WindowComponents>(windowComponents);
    }

    return this
        ->  windowComponents.get();
}

Window *Self::GetMainWindow() noexcept {
    return  this
        ->  Impl
        ->  mainWindow;
}

Button *Self::GetSettingButton() noexcept{
    return this
        ->  Impl
        ->  settingButton;
}

Layout *Self::GetLayout() noexcept {
    return this 
        ->  Impl
        ->  layout;
}

Self *Self::WhenDone() noexcept {
    #if defined (Z_DEBUG)
        using Assert = AssertContext;
        using Log = LogContext;

        Assert{}.RequireNonNullPtr(Impl.get());
        Assert{}.RequireNonNullPtr(Impl->mainWindow);
        Assert{}.RequireNonNullPtr(Impl->settingButton);

        Log{}.LogDebug(Impl.get());
        Log{}.LogDebug(Impl->mainWindow);
        Log{}.LogDebug(Impl->settingButton);
    #endif

    return this;
}

void Self::Finally_Add_Listener() noexcept {
    // const auto window = this->GetMainWindow();
    const auto settingButton = this->GetSettingButton();
    const auto windowComponents = this->GetWindowComponents();
    const auto layout = this->GetLayout();

    using Impl = SettingWindowLayoutData;
    if(!layoutManager) {
        Utils::MakeSmartPtr<LayoutManager>(layoutManager);
    }
    layoutManager
        ->  StartBuild()
        ->  WithAndThen(&Impl::componentsManager, windowComponents)
        ->  WithAndThen(&Impl::layout, layout)
        ->  WhenDone()
        ->  SetupSettingWindowLayout();
}