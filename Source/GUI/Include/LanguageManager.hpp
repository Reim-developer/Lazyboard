#ifndef LANGUAGE_MANAGER_HPP
#define LANGUAGE_MANAGER_HPP
#include <QObject>
#include <QSettings>
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../../Lib_Memory/Include/Memory.hpp"

using ZClipboard::Lib_Memory::PtrUnique;

GUI_NAMESPACE

    class LanguageManager : public QObject {
        Q_OBJECT

        public:
            LanguageManager();
            static LanguageManager &GetLanguageManager();
            void SetLanguage(int languageType);

        signals:
            void OnLanguageChanged(int languageType);

        private:
            PtrUnique<QSettings> settings;
    };

END_NAMESPACE

#endif  // LANGUAGE_MANAGER_HPP