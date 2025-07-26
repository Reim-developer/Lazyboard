#ifndef LISTENER_OPEN_SETTING_WINDOW_HPP
#define LISTENER_OPEN_SETTING_WINDOW_HPP
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../../GUI/Windows/Include/SettingWindow.hpp"

using ZClipboard::GUI::Windows::SettingWindowManager;

LISTENER_NAMESPACE

    class ListenerOpenSettingWindow {
        private:
            using WindowManager = SettingWindowManager;
            using Self = ListenerOpenSettingWindow;
            using Button = QPushButton;

        private:
            PtrUnique<WindowManager> windowManager;
            Button *settingButton;

        public:
            Self *StartBuild(Button *settingButton);
            void SetupListener();
    };

END_NAMESPACE

#endif // LISTENER_OPEN_SETTING_WINDOW_HPP