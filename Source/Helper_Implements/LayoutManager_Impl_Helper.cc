#include "Include/LayoutManager_Impl_Helper.hpp"
#include "../GUI/Toolkit/Include/LayoutManager_Tookit.hpp"
using ZClipboard::GUI::Toolkit::LayoutMangerTookit;
using ZClipboard::GUI::Toolkit::LayoutMangerTookitData;
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