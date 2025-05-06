#ifndef zSearchPanel_HPP
#define zSearchPanel_HPP
#include <QObject>
#include <QString>
#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include "zClipboardModel.hpp"
#include "ztable.hpp"

using zclipboard::zGui::ZTable;
using zclipboard::zGui::zTableModel;

namespace zclipboard::zGui {
class SearchArea : public QObject {
    Q_OBJECT

   public:
    void addSearchPanel(QWidget *zWindow, QGridLayout *zLayout, ZTable *table);

   private:
    QLineEdit *zLineEdit;
};
}  // namespace zclipboard::zGui

#endif  // zSearchPanel_HPP