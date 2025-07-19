#ifndef Manager_MainWindow_Component_Impl
#define Manager_MainWindow_Component_Impl
#include "../../../Utils/Include/Namespace_Macro.hpp"
#include "../../../Helper_Implements/Include/MainWindow_GUI_Impl_Helper.hpp"

IMPLEMENTS_NAMESPACE
    class MainWindowComponentsManager {
        public:
            void Render_MainWindow_GUI(Object *object, Toolkit *toolkit, QIcon appIcon);
    };

END_NAMESPACE

#endif // Manager_MainWindow_Component_Impl