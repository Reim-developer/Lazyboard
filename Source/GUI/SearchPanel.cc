#include "Include/SearchPanel.hpp"
#include <QLineEdit>
#include <QTimer>
#include <QString>
#include "Include/TableView.hpp"

using ZClipboard::GUI::SearchArea;

SearchArea *SearchArea::StartBuild() {
    Utils::MakeSmartPtr<Implement>(Impl);

    return this;
}

SearchArea *SearchArea::WhenDone() {
    return this;
}

QLineEdit *SearchArea::GetSearchPanel() {
    auto searchLine = this
        ->  Impl
        ->  tookit
        ->  GetSearchArea();

    return searchLine;
}

void SearchArea::SetupSearchPanel() {
    auto searchLine = this->GetSearchPanel();

    auto windowLayout = this
        ->  Impl
        ->  layout;

    auto tableView = this
        ->  Impl
        ->  tableView;

    searchLine->setPlaceholderText("Search...");
    windowLayout->addWidget(searchLine, 0, 0);

    auto modelTable = tableView->GetTableModel();
    
    QObject::connect(searchLine, &QLineEdit::textChanged, [modelTable](const QString &text) {
        QTimer::singleShot(300, modelTable, [modelTable, text]() { 
            modelTable->filterItems(text); 
        });
    });
}
