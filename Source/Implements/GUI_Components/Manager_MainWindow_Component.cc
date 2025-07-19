#include "Include/Manager_MainWindow_Component_Impl.hpp"

using ZClipboard::Implements::MainWindowComponentsManager;

using Self = MainWindowComponentsManager;

void Self::Render_MainWindow_GUI(Object *object, Toolkit *toolkit, QIcon appIcon) {
    ClearButtonComponentImpl(object, toolkit);
    SearchAreaComponentImpl(object, toolkit);
    TableViewComponentImpl(object, toolkit);
    NotificationComponentImpl(object, toolkit);
    SystemTrayComponentImpl(object, toolkit, appIcon);
}