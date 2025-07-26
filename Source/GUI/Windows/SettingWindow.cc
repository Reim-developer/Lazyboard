#include "Include/SettingWindow.hpp"
#include "../../Utils/Include/Utils.hpp"
#include <QDialog>
#include <QGridLayout>

using ZClipboard::GUI::Windows::SettingWindowManager;
using ZClipboard::Core::CoreSettingWindowData;
using ZClipboard::AppUtils::Utils;

using Self = SettingWindowManager;
using Window = QDialog;
using Layout = QGridLayout;
using Button = QPushButton;

#if defined (Z_DEBUG)
    #include "../../Utils/Include/AssertNullPtr.hpp"
    #include "../../Utils/Include/Logging.hpp"

    using ZClipboard::AppUtils::LogContext;

    using Log = LogContext;
    using Assert = AssertContext;
#endif

void Self::ShowSettingWindow(Button *settingButton) {
    Utils::MakeSmartPtr<Window>(settingWindow);
    Utils::MakeSmartPtr<Layout>(windowLayout, settingWindow.get());
    Utils::MakeSmartPtr<CoreBuilder>(coreBuilder);
    Utils::MakeSmartPtr<WindowComponents>(components);

    #if defined (Z_DEBUG)
        Assert{}.RequireNonNullPtr(coreBuilder.get());
        Assert{}.RequireNonNullPtr(settingWindow.get());
        Assert{}.RequireNonNullPtr(windowLayout.get());
        Assert{}.RequireNonNullPtr(components.get());

        Log{}.LogDebug(settingWindow.get());
        Log{}.LogDebug(windowLayout.get());
        Log{}.LogDebug(coreBuilder.get());
        Log{}.LogDebug(components.get());
    #endif 

    using Impl = CoreSettingWindowData;
    coreBuilder
        ->  StartBuild()
        ->  WithLayout(windowLayout.get())
        ->  WhenDone()
        ->  SetupWindow(components.get());

    settingWindow->setMinimumSize(400, 400);
    settingWindow->show();
}