#include "include/zSearchPanel.hpp"
#include <QLineEdit>

using zclipboard::zGui::SearchArea;

void SearchArea::addSearchPanel(QWidget *zWindow, QGridLayout *zLayout) {
    zLineEdit = new QLineEdit(zWindow);
    zLineEdit->setPlaceholderText("Search...");
    zLayout->addWidget(zLineEdit, 0, 0);
}