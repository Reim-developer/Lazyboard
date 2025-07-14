#include "../../../Utils/Include/Namespace_Macro.hpp"
#include "../../Include/LanguageManager.hpp"
#include "../../../Utils/Include/Alias_Template.hpp"
#include "../../../Utils/Include/Meta_Macro.hpp"
#include "../../../Lib_Memory/Include/Memory.hpp"
#include <QMainWindow>


using ZClipboard::GUI::LanguageManager;
using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::Lib_Memory::MakePtr;
using ZClipboard::AppUtils::Func;

GUI_HOT_RELOAD_NAMESPACE
    struct HotReloadImpl {
        QMainWindow *windowContext;
    };

    class HotReloadLanguage {
        private:
            PtrUnique<HotReloadImpl> Impl;
            using Implements = HotReloadImpl;

        public:
            

            HotReloadLanguage *StartBuild();

            CLASS_BUILD(T, V)
            HotReloadLanguage *WithAndThen(T Implements::*member, V &&value) {
                Impl.get()->*member = FORWARD(V, value);

                return this;
            }
            
            HotReloadLanguage *WhenDone();

            void ThenAddListener(Func<void()> Function);
    };

END_NAMESPACE