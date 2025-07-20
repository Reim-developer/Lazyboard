#include "Include/LayoutManager_Impl_Helper.hpp"
#include "../GUI/Toolkit/Include/MainWindow_LayoutManager.hpp"
using ZClipboard::GUI::Toolkit::MainWindowLayoutManager;
using ZClipboard::GUI::Toolkit::LayoutMangerToolkitData;
using ZClipboard::Lib_Memory::MakePtr;
using ZClipboard::Lib_Memory::PtrUnique;

void SetupAppLayout(Toolkit *tookit, QGridLayout *layout) {
    using LayoutManager = LayoutMangerTookit;
    using Impl = LayoutMangerTookitData;

    PtrUnique<LayoutManager> layoutManager = MakePtr<LayoutManager>();

    layoutManager
        ->  StartBuild()
        ->  WithAndThen(&Impl::tookit, tookit)
        ->  WithAndThen(&Impl::layout, layout)
        ->  WhenDone()
        ->  SetupAppGridLayout();
}