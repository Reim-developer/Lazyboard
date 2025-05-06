#include "include/clearButton.hpp"
#include <QGridLayout>
#include <QPushButton>
#include <QVariant>
#include <QTimer>
#include "include/ztable.hpp"

using zclipboard::zGui::ClearButton;

void ClearButton::addClearButton(QGridLayout *layout, ZTable *table) {
    clearButton = new QPushButton();
    clearButton->setText("Clear Clipboard");
    layout->addWidget(clearButton, 0, 1);

    connect(clearButton, &QPushButton::clicked, this, [=]() {
        QString query = R"(
            DROP TABLE IF EXISTS clipboard
        )";
        table->getZSQL().executeQuery(query, QVariantMap());
        clearButton->setText("Cleaned Clipboard");
        table->getZModel()->clearData();

        QTimer::singleShot(1500, [this]() { clearButton->setText("Clear Clipboard"); });
    });
}