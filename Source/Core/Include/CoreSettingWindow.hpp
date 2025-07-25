#ifndef CORE_SETTING_WINDOW_HPP
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../../Utils/Include/Meta_Macro.hpp"
#include "../../GUI/Toolkit/Include/SettingWindow_Components.hpp"
#include "../../GUI/Toolkit/Include/SettingWindow_LayoutManager.hpp"
#include "../../Lib_Memory/Include/Memory.hpp"
#include <QPushButton>
#include <QMainWindow>

using ZClipboard::GUI::Toolkit::SettingWindowComponentsManager;
using ZClipboard::GUI::Toolkit::SettingWindowLayoutManager;
using ZClipboard::Lib_Memory::PtrUnique;

CORE_NAMESPACE

    struct CoreSettingWindowData {
        QPushButton *settingButton;
        QMainWindow *mainWindow;
        QGridLayout *layout;
    };

    class CoreSettingWindow {
        private:
            using Self = CoreSettingWindow;
            using WindowComponents = SettingWindowComponentsManager;
            using LayoutManager = SettingWindowLayoutManager;
            using ImplData = CoreSettingWindowData;
            using Window = QMainWindow;
            using Button = QPushButton;
            using Layout = QGridLayout;
 
        private:
            PtrUnique<WindowComponents> windowComponents;
            PtrUnique<ImplData> Impl;
            PtrUnique<LayoutManager> layoutManager;

        private:
            WindowComponents *GetWindowComponents() noexcept;
            Window *GetMainWindow() noexcept;
            Button *GetSettingButton() noexcept;
            Layout *GetLayout() noexcept;

        public:
            Self *StartBuild() noexcept;

            CLASS_BUILD(T, V)
            inline Self *WithAndThen(T ImplData::*member, V &&value) noexcept {
                Impl.get()->*member = FORWARD(V, value);

                return this;
            }

            Self *WhenDone() noexcept;
            void Finally_Add_Listener() noexcept;
    };

END_NAMESPACE
#endif // CORE_SETTING_WINDOW_HPP