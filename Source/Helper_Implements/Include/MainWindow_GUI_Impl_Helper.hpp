#ifndef MAIN_WINDOW_GUI_IMPL_HELPER_HPP
#define MAIN_WINDOW_GUI_IMPL_HELPER_HPP

#include "../../Lib_Memory/Include/MainWindow_ObjectManager.hpp"
#include "../../GUI/Toolkit/Include/MainWindow_Components.hpp"
#include <QIcon>

using ZClipboard::Lib_Memory::MainWindowObjectManager;
using ZClipboard::GUI::Toolkit::MainWindowComponentsManager;

using Object = MainWindowObjectManager;
using ComponentsManager = MainWindowComponentsManager;
using Window = QMainWindow;

void ClearButtonComponentImpl(Object *object, ComponentsManager *toolkit);
void SearchAreaComponentImpl(Object *object, ComponentsManager *toolkit);
void TableViewComponentImpl(Object *object, ComponentsManager *toolkit);
void NotificationComponentImpl(Object *object, ComponentsManager *toolkit);
void SystemTrayComponentImpl(Window *window, Object *object, ComponentsManager *toolkit, QIcon appIcon);
void ConnectButtonComponentImpl(Window *window, Object *object, ComponentsManager *toolkit);
void DisconnectButtonComponentImpl(Window *window, Object *object, ComponentsManager *toolkit);
void SettingButtonComponentImpl(Window *window, Object *object, ComponentsManager *toolkit);

#endif // MAIN_WINDOW_GUI_IMPL_HELPER_HPP