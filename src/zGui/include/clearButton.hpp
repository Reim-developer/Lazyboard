#ifndef CLEAR_BUTTON_HPP
#define CLEAR_BUTTON_HPP
#include <QGridLayout>
#include <QPushButton>
#include <QObject>
#include "ztable.hpp"
#include <QSettings>
#include "../../lib_memory/include/memory.hpp"
#include "../../core/include/clear.hpp"
#include "../../listener/include/clearCacheListener.hpp"

using zclipboard::zGui::ZTable;
using zclipboard::lib_memory::PtrUnique;
using zclipboard::core::ClearCoreBuilder;
using zclipboard::listener::ClearCacheListener;

namespace zclipboard::zGui {
class ClearButton  {
    private:
        ClearCoreBuilder BuilderCore;
        ClearCacheListener BuilderFunc;

   public:
    void addClearButton(QGridLayout *layout, ZTable* table);
    QPushButton *getClearButton();

   private:

    PtrUnique<QSettings> settings;
    PtrUnique<QPushButton> clearButton;
};
}  // namespace zclipboard::zGui

#endif  // CLEAR_BUTTON_HPP