#ifndef zSearchPanel_HPP
#define zSearchPanel_HPP
#include <QObject>
#include <QString>
#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include "TableModel.hpp"
#include "TableView.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"

using ZClipboard::GUI::TableView;
using ZClipboard::GUI::TableModel;

GUI_NAMESPACE

    struct SearchPanelWidget {
        QWidget *window;
        QGridLayout *layout;
        TableView *tableView;
    };

    class SearchArea : public QObject {
        Q_OBJECT

    public:
        void SetupSearchPanel(const SearchPanelWidget &search);
        QLineEdit *GetSearchPanel();

    private:
        QLineEdit *zLineEdit;
    };

END_NAMESPACE

#endif  // zSearchPanel_HPP