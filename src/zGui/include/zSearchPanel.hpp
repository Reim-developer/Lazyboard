#ifndef zSearchPanel_HPP
#define zSearchPanel_HPP
#include <QObject>
#include <QString>
#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include "zClipboardModel.hpp"

using zclipboard::zGui::zTableModel;

namespace zclipboard::zGui {
class SearchArea : public QObject {
    Q_OBJECT

   public:
    void addSearchPanel(QWidget *zWindow, QGridLayout *zLayout, zTableModel *zModel);

   private:
    QLineEdit *zLineEdit;
};
}  // namespace zclipboard::zGui

#endif  // zSearchPanel_HPP