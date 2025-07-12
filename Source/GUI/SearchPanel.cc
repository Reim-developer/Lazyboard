#include "Include/SearchPanel.hpp"
#include <QLineEdit>
#include <QVariant>
#include <QList>
#include <QTimer>
#include "Include/TableView.hpp"

using ZClipboard::GUI::SearchArea;

void SearchArea::SetupSearchPanel(const SearchPanelWidget &search) {
    zLineEdit = new QLineEdit(search.window);
    zLineEdit->setPlaceholderText("Search...");
    search.layout->addWidget(zLineEdit, 0, 0);

    auto zModel = search.tableView->GetTableModel();
    
    connect(zLineEdit, &QLineEdit::textChanged, this, [zModel](const QString &text) {
        QTimer::singleShot(300, zModel, [zModel, text]() { zModel->filterItems(text); });
    });
}

QLineEdit *SearchArea::GetSearchPanel() {
    return zLineEdit;
}