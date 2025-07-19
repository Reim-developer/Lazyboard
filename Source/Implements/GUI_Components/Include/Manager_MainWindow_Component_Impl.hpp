#ifndef Manager_MainWindow_Component_Impl
#define Manager_MainWindow_Component_Impl
#include <QMainWindow>
#include "../../../Utils/Include/Namespace_Macro.hpp"
#include "../../../Utils/Include/Meta_Macro.hpp"
#include "../../../Lib_Memory/Include/Memory.hpp"
#include "../../../Helper_Implements/Include/MainWindow_GUI_Impl_Helper.hpp"

using ZClipboard::Lib_Memory::PtrUnique;

IMPLEMENTS_NAMESPACE
    
    struct MainWindowComponentsManagerData {
        Object *object;
        Toolkit *toolkit;
        QIcon *appIcon;
        QMainWindow *window;
    };

    class MainWindowComponentsManager {
        private:
            using Self = MainWindowComponentsManager;
            using DataImpl = MainWindowComponentsManagerData;
            using Window = QMainWindow;

        private:
            PtrUnique<DataImpl> Impl;
        
        private:
            Object *GetObject();
            Toolkit *GetToolkit();
            QIcon *GetAppIcon();
            Window *GetWindow();

        public:
            Self *StartBuild();

            CLASS_BUILD(T, V)
            Self *WithAndThen(T DataImpl::*member, V &&value) {
                Impl.get()->*member = FORWARD(V, value);

                return this;
            }

            Self *WhenDone();
            void Render_MainWindow_GUI();
    };

END_NAMESPACE

#endif // Manager_MainWindow_Component_Impl