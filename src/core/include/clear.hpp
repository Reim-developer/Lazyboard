#ifndef CORE_CLEAR_HPP
#define CORE_CLEAR_HPP
#include <QObject>
#include <QPushButton>
#include <QSettings>
#include <functional>
#include "../../zGui/include/ztable.hpp"
#include "../../lib_memory/include/memory.hpp"

using std::function;
using zclipboard::lib_memory::MakePtr;
using zclipboard::lib_memory::PtrUnique;
using zclipboard::zGui::ZTable;

namespace zclipboard::core {
    struct ParamImpl {
        QPushButton *button;
    };

    class ClearCoreBuilder {
    private:
        PtrUnique<ParamImpl> params;

    public:
        ClearCoreBuilder *StartBuild(QPushButton* button);
        void ThenAddListener(function<void()> func);
    };
}
#endif  // CORE_CLEAR_HPP