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

struct SearchPanelWidget {
    QWidget *zWindow;
    QGridLayout *zLayout;
    ZTable *table;
};
class SearchArea : public QObject {
    Q_OBJECT

   public:
    void addSearchPanel(const SearchPanelWidget &search);
    QLineEdit *getSearchPanel();

   private:
    QLineEdit *zLineEdit;
};
}  // namespace zclipboard::zGui

#endif  // zSearchPanel_HPP