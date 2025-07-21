#include "Include/ClearButton.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Core/Include/CoreClearCache.hpp"
#include "Include/TableView.hpp"
#include "../Utils/Include/Utils.hpp"

using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::GUI::ClearButton;
using ZClipboard::Core::CoreClearBuilderData;
using ZClipboard::AppUtils::Utils;

#if defined (Z_DEBUG)
    #include "../Utils/Include/AssertNullPtr.hpp"
#endif

void ClearButton::SetupClearButton(ComponentsManager *toolkit, TableView *tableView) {
    auto clearButton = toolkit->GetClearButton();
    Utils::MakeSmartPtr<QSettings>(settings, AUTHOR_NAME, APP_NAME);
    
    SetupEventListener(clearButton, tableView);
    #if defined (Z_DEBUG)
        __LOGGING_ALL_OBJECTS__(clearButton);
    #endif
}

void ClearButton::SetupEventListener(QPushButton *clearButton, TableView *tableView) {
    #if defined (Z_DEBUG)

        AssertContext{}.RequireNonNullPtr(clearButton);
        AssertContext{}.RequireNonNullPtr(settings.get());
        AssertContext{}.RequireNonNullPtr(tableView);

    #endif

    if(!BuilderCore) {
        Utils::MakeSmartPtr<CoreClearBuilder>(BuilderCore);
    }

    using ImplData = CoreClearBuilderData;
    BuilderCore
        ->  StartBuild()
        ->  WithAndThen(&ImplData::button, clearButton)
        ->  WithAndThen(&ImplData::settings, settings.get())
        ->  WithAndThen(&ImplData::tableView, tableView)
        ->  WhenDone()
        ->  Finally_Setup_Listener();   
}
