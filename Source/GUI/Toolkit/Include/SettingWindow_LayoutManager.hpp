#ifndef SETTING_WINDOW_LAYOUT_MANAGER_HPP
#define SETTING_WINDOW_LAYOUT_MANAGER_HPP
#include "../../../Utils/Include/Namespace_Macro.hpp"
#include "Layout_Toolkit.hpp"
#include "SettingWindow_Components.hpp"
#include "../../../Lib_Memory/Include/Memory.hpp"
#include "../../../Utils/Include/Meta_Macro.hpp"
#include <QGridLayout>

using ZClipboard::GUI::Toolkit::SettingWindowComponentsManager;
using ZClipboard::Lib_Memory::PtrUnique;

GUI_TOOLKIT_NAMESPACE

    struct SettingWindowLayoutData {
        QGridLayout *layout;
        SettingWindowComponentsManager *componentsManager;
    };

    class SettingWindowLayoutManager {
        private:
            using Self = SettingWindowLayoutManager;
            using Widget = WidgetProperty;
            using DataImpl = SettingWindowLayoutData;
            using Layout = QGridLayout;
            using ComponentsManager = SettingWindowComponentsManager;

        private:
            PtrUnique<DataImpl> Impl;

        public:
            Self *StartBuild();

            CLASS_BUILD(T, V)
            Self *WithAndThen(T DataImpl::*member, V &&value) {
                Impl.get()->*member = FORWARD(V, value);

                return this;
            }

            Self *WhenDone();

            Layout *GetLayout();
            ComponentsManager *GetComponentsManager();

            Widget GetSetPasswordButtonLayout();

            void SetupSettingWindowLayout();

    };

END_NAMESPACE

#endif 