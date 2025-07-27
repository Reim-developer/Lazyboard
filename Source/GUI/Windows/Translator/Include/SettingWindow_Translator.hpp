#ifndef SETTING_WINDOW_TRANSLATOR_HPP
#define SETTING_WINDOW_TRANSLATOR_HPP
#include "../../../../Utils/Include/Namespace_Macro.hpp"
#include "../../../../Lib_Memory/Include/Memory.hpp"
#include "../../../../GUI/Toolkit/Include/SettingWindow_Components.hpp"
#include <QSettings>
#include <QDialog>

using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::GUI::Toolkit::SettingWindowComponentsManager;

GUI_WINDOW_TRANSLATOR_NAMESPACE

    class SettingWindowTranslator {
        private:
            using Settings = QSettings;
            using Components = SettingWindowComponentsManager;
            using Window = QDialog;

        private:
            PtrUnique<Settings> settings;

        private:
            void VietNameseTranslator(Window *window, Components *components);
            void EnglishTranslator(Window *window, Components *components);

        public:
            void LoadTranslator(Window *window, Components *components);
    };

END_NAMESPACE

#endif // SETTING_WINDOW_TRANSLATOR_HPP