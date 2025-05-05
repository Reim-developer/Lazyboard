#include "include/zSearchPanel.hpp"
#include <QLineEdit>
#include <QVariant>
#include <QList>
#include <QTimer>

using zclipboard::zGui::SearchArea;

void SearchArea::addSearchPanel(QWidget *zWindow, QGridLayout *zLayout, zTableModel *zModel) {
    zLineEdit = new QLineEdit(zWindow);
    zLineEdit->setPlaceholderText("Search...");
    zLayout->addWidget(zLineEdit, 0, 0);

    connect(zLineEdit, &QLineEdit::textChanged, this, [zModel](const QString &text) {
        QTimer::singleShot(300, zModel, [zModel, text]() { zModel->filterItems(text); });
    });
}
