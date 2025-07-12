#ifndef CORE_CLEAR_HPP
#define CORE_CLEAR_HPP
#include <QObject>
#include <QPushButton>
#include <QSettings>
#include <functional>
#include "../../GUI/Include/TableView.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../../Lib_Memory/Include/Memory.hpp"

using std::function;
using ZClipboard::Lib_Memory::MakePtr;
using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::GUI::TableView;

CORE_NAMESPACE

    struct ParamImpl {
        QPushButton *button;
    };

    class ClearCoreBuilder {
    private:
        PtrUnique<ParamImpl> Impl;

    public:
        ClearCoreBuilder *StartBuild(QPushButton* button);
        void ThenAddListener(function<void()> func);
    };

END_NAMESPACE
#endif  // CORE_CLEAR_HPP