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

Self *Self::StartBuild() noexcept {
    if(!Impl) {
        Utils::MakeSmartPtr<DataImpl>(Impl);
    }

    return this;
}

Layout *Self::GetLayout() noexcept {
    auto layout = this
        ->  Impl
        ->  layout;

    #if defined (Z_DEBUG)
        AssertContext{}.RequireNonNullPtr(layout);

        LogContext{}.LogDebug(&layout);
    #endif 

    return layout;
}

ComponentsManager *Self::GetComponentsManager() noexcept {
    auto componentsManager = this
        ->  Impl
        ->  componentsManager;

    #if defined (Z_DEBUG)
        AssertContext{}.RequireNonNullPtr(componentsManager);

        LogContext{}.LogDebug(&componentsManager);
    #endif 

    return componentsManager;
}

Self *Self::WhenDone() noexcept {
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

Widget Self::GetSetPasswordButtonLayout(
            Layout *layout, 
            ComponentsManager *componentsManager) const noexcept {

    auto setPasswordButton = componentsManager->GetSetPasswordButton();

    const auto widgetData = Widget {
        .widget = setPasswordButton,
        .row = 3, .column = 2
    };

    return widgetData;
}

Widget Self::GetHideWindowSettingCheckboxLayout(
            Layout *layout,
            ComponentsManager *componentsManager) const noexcept {
    
    auto autoHideCheckbox = componentsManager->GetHideSettingCheckBox();

    const auto widgetData = Widget {
        .widget = autoHideCheckbox,
        .row = 0, .column = 0
    };

    return widgetData;
}

Widget Self::GetNotificationCheckboxLayout(
            Layout *layout,
            ComponentsManager *componentsManager) const noexcept {

    auto notificationCheckbox = componentsManager->GetNotificationCheckBox();

    const auto widgetData = Widget {
        .widget = notificationCheckbox,
        .row = 1, .column = 0
    };

    return widgetData;
}

Widget Self::GetLanguageListBoxLayout(
            Layout *layout,
            ComponentsManager *componentsManager) const noexcept {

    auto languageListBox = componentsManager->GetLanguageListBox();
    
    const auto widgetData = Widget {
        .widget = languageListBox,
        .row = 2, .column = 0
    };

    return widgetData;
}

Widget Self::GetThemeListBoxLayout(
            Layout *layout, 
            ComponentsManager *componentsManager) const noexcept {
    
    auto themeListBox = componentsManager->GetThemeListBox();

    const auto widgetData = Widget {
        .widget = themeListBox,
        .row = 3, .column = 0
    };

    return widgetData;
}

Widget Self::GetLanguageLabelLayout(
            Layout *layout, 
            ComponentsManager *componentsManager) const noexcept {

    auto languageLabel = componentsManager->GetLanguageDescription();

    const auto widgetData = Widget {
        .widget = languageLabel,
        .row = 2, .column = 1
    };

    return widgetData;
}

Widget Self::GetThemeLabelLayout(
            Layout *layout,
            ComponentsManager *componentsManager) const noexcept {

    auto themeLabel = componentsManager->GetThemeDescription();

    const auto widgetData = Widget {
        .widget = themeLabel,
        .row = 3, .column = 1
    };

    return widgetData;
}

void Self::SetupSettingWindowLayout() noexcept {
    auto layout = this->GetLayout();
    auto componentsManager = this->GetComponentsManager();

    const auto passwordButtonLayout = this->GetSetPasswordButtonLayout(layout, componentsManager);
    const auto hideWindowSettingCheckboxLayout = this->GetHideWindowSettingCheckboxLayout(layout, componentsManager);
    const auto notificationCheckboxLayout = this->GetNotificationCheckboxLayout(layout, componentsManager);
    const auto languageListBoxLayout = this->GetLanguageListBoxLayout(layout, componentsManager);
    const auto themeListBoxLayout = this->GetThemeListBoxLayout(layout, componentsManager);
    const auto languageLabelLayout = this->GetLanguageLabelLayout(layout, componentsManager);
    const auto themeLabelLayout = this->GetThemeLabelLayout(layout, componentsManager);

    GridLayoutAdd(
        layout, 
        passwordButtonLayout, hideWindowSettingCheckboxLayout,
        notificationCheckboxLayout, languageListBoxLayout,
        themeListBoxLayout, languageLabelLayout,
        themeLabelLayout
    );
}