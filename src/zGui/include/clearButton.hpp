#ifndef CLEAR_BUTTON_HPP
#define CLEAR_BUTTON_HPP
#include <QGridLayout>
#include <QPushButton>
#include <QObject>
#include "ztable.hpp"
#include <QSettings>

using zclipboard::zGui::ZTable;

namespace zclipboard::zGui {
class ClearButton : public QObject {
    Q_OBJECT
   public:
    void addClearButton(QGridLayout *layout, ZTable *table);
    QPushButton *getClearButton();

   private:
    QSettings *settings;
    QPushButton *clearButton;
};
}  // namespace zclipboard::zGui

#endif  // CLEAR_BUTTON_HPP