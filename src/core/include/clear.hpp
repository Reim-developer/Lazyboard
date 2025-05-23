#ifndef CORE_CLEAR_HPP
#define CORE_CLEAR_HPP
#include <QObject>
#include <QPushButton>
#include <QSettings>
#include "../../zGui/include/ztable.hpp"

using zclipboard::zGui::ZTable;

namespace zclipboard::core {

// clang-format off
struct ClearCoreParams {
    ZTable *table;
    QPushButton *button;
    QSettings *settings;
};
// clang-format on

class ClearCore : QObject {
    Q_OBJECT

   public:
    void clearCache(const ClearCoreParams &params);
};
}  // namespace zclipboard::core

#endif  // CORE_CLEAR_HPP