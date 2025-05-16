#include "include/zSearchPanel.hpp"
#include <QLineEdit>
#include <QVariant>
#include <QList>
#include <QTimer>
#include "include/ztable.hpp"

using zclipboard::zGui::SearchArea;

void SearchArea::addSearchPanel(const SearchPanelWidget &search) {
    zLineEdit = new QLineEdit(search.zWindow);
    zLineEdit->setPlaceholderText("Search...");
    search.zLayout->addWidget(zLineEdit, 0, 0);

    auto zModel = search.table->getZModel();
    connect(zLineEdit, &QLineEdit::textChanged, this, [zModel](const QString &text) {
        QTimer::singleShot(300, zModel, [zModel, text]() { zModel->filterItems(text); });
    });
}
