#ifndef MAIN_WINDOW_GUI_IMPL_HELPER_HPP
#define MAIN_WINDOW_GUI_IMPL_HELPER_HPP

#include "../../Lib_Memory/Include/MainWindow_ObjectManager.hpp"
#include "../../GUI/Toolkit/Include/Components_Toolkit.hpp"
#include <QIcon>

using ZClipboard::Lib_Memory::MainWindowObjectManager;
using ZClipboard::GUI::Toolkit::ComponentsToolkit;

using Object = MainWindowObjectManager;
using Toolkit = ComponentsToolkit;

void ClearButtonComponentImpl(Object *object, Toolkit *toolkit);
void SearchAreaComponentImpl(Object *object, Toolkit *toolkit);
void TableViewComponentImpl(Object *object, Toolkit *toolkit);
void NotificationComponentImpl(Object *object, Toolkit *toolkit);
void SystemTrayComponentImpl(Object *object, Toolkit *toolkit, QIcon appIcon);

#endif // MAIN_WINDOW_GUI_IMPL_HELPER_HPP