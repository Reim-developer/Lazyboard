#include "Include/SettingWindow_LayoutManager.hpp"
#include "Include/Layout_Toolkit.hpp"
#include "../../Utils/Include/Utils.hpp"

using ZClipboard::GUI::Toolkit::SettingWindowLayoutManager;
using ZClipboard::GUI::Toolkit::WidgetProperty;
using ZClipboard::AppUtils::Utils;

using Self = SettingWindowLayoutManager;
using Widget = WidgetProperty;
using Layout = QGridLayout;
using ComponentsManager = SettingWindowComponentsManager;

#if defined (Z_DEBUG)
    #include "../../Utils/Include/AssertNullPtr.hpp"
    #include "../../Utils/Include/Logging.hpp"
    
    using ZClipboard::AppUtils::LogContext;
#endif

Self *Self::StartBuild() {
    if(!Impl) {
        Utils::MakeSmartPtr<DataImpl>(Impl);
    }

    return this;
}

Layout *Self::GetLayout() {
    auto layout = this
        ->  Impl
        ->  layout;

    #if defined (Z_DEBUG)
        AssertContext{}.RequireNonNullPtr(layout);

        LogContext{}.LogDebug(&layout);
    #endif 

    return layout;
}

ComponentsManager *Self::GetComponentsManager() {
    auto componentsManager = this
        ->  Impl
        ->  componentsManager;

    #if defined (Z_DEBUG)
        AssertContext{}.RequireNonNullPtr(componentsManager);

        LogContext{}.LogDebug(&componentsManager);
    #endif 

    return componentsManager;
}

Self *Self::WhenDone() {
    #if defined (Z_DEBUG)
        AssertContext{}.RequireNonNullPtr(Impl.get());
        AssertContext{}.RequireNonNullPtr(Impl->componentsManager);
        AssertContext{}.RequireNonNullPtr(Impl->layout);

        LogContext{}.LogDebug(Impl.get());
        LogContext{}.LogDebug(&Impl->layout);
        LogContext{}.LogDebug(&Impl->componentsManager);
    #endif 

    return this;
}

Widget Self::GetSetPasswordButtonLayout() {
    auto componentsManager = this->GetComponentsManager();
    auto layout = this->GetLayout();

    auto setPasswordButton = componentsManager->GetSetPasswordButton();

    auto widgetData = Widget {
        .widget = setPasswordButton,
        .row = 3, .column = 2
    };

    return widgetData;
}