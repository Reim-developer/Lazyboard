#ifndef LayoutManager_Impl_Helper
#define LayoutManager_Impl_Helper
#include "../../GUI/Toolkit/Include/MainWindow_Components.hpp"
#include <QGridLayout>

using ZClipboard::GUI::Toolkit::MainWindowComponentsManager;
using ComponentsManager = MainWindowComponentsManager;

void SetupAppLayout(ComponentsManager *tookit, QGridLayout *layout);

#endif // LayoutManager_Impl_Helper