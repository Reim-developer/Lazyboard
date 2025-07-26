#include "Include/ListenerOpenSettingWindow.hpp"
#include "../Utils/Include/Utils.hpp"

using ZClipboard::Listener::ListenerOpenSettingWindow;
using ZClipboard::AppUtils::Utils;
using Self = ListenerOpenSettingWindow;

#if defined (Z_DEBUG)
    #include "../Utils/Include/AssertNullPtr.hpp"
    #include "../Utils/Include/Logging.hpp"

    using ZClipboard::AppUtils::LogContext;

    using Assert = AssertContext;
    using Log = LogContext;
#endif 

Self *Self::StartBuild(Button *settingButton) {
    this->settingButton = settingButton;

    #if defined (Z_DEBUG)
        //Assert{}.RequireNonNullPtr(windowManager.get());
        Assert{}.RequireNonNullPtr(settingButton);

        //Log{}.LogDebug(windowManager.get());
        Log{}.LogDebug(settingButton);
    #endif

    return this;
}

void Self::SetupListener() {    
    const auto Fn = [this]{
        Utils::MakeSmartPtr<WindowManager>(windowManager);
        
        #if defined (Z_DEBUG)
            Assert{}.RequireNonNullPtr(windowManager.get());
            Assert{}.RequireNonNullPtr(this->settingButton);

            Log{}.LogDebug(windowManager.get());
            Log{}.LogDebug(this->settingButton);
        #endif

        windowManager->ShowSettingWindow(this->settingButton);
    };

    QObject::connect(this->settingButton, &QPushButton::clicked, Fn);
}