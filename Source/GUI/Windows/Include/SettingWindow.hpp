#ifndef SETTING_WINDOW_HPP
#define SETTING_WINDOW_HPP
#include "../../../Utils/Include/Namespace_Macro.hpp"
#include "../../../Core/Include/CoreSettingWindow.hpp"
#include "../../../Lib_Memory/Include/Memory.hpp"
#include <QPushButton>

using ZClipboard::Core::CoreSettingWindow;
using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::GUI::Toolkit::SettingWindowComponentsManager;

GUI_WINDOW_NAMESPACE

    class SettingWindowManager {
        private:
            using CoreBuilder = CoreSettingWindow;
            using Window = QDialog;
            using Layout = QGridLayout;
            using WindowComponents = SettingWindowComponentsManager;

        private:
            PtrUnique<CoreBuilder> coreBuilder;
            PtrUnique<Window> settingWindow;
            PtrUnique<Layout> windowLayout;
            PtrUnique<WindowComponents> components;

        public:
            void ShowSettingWindow(QPushButton *settingButton);
    };

END_NAMESPACE

#endif // SETTING_WINDOW_HPP