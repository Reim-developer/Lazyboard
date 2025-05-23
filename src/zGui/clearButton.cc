#include "include/clearButton.hpp"
#include <QGridLayout>
#include <QPushButton>
#include <QVariant>
#include <QTimer>
#include "include/ztable.hpp"
#include "../zUtils/include/config.hpp"
#include <QSettings>
#include "../core/include/clear.hpp"

using zclipboard::core::ClearCore;
using zclipboard::core::ClearCoreParams;
using zclipboard::zGui::ClearButton;

void ClearButton::addClearButton(QGridLayout *layout, ZTable *table) {
    clearButton = new QPushButton();
    settings = new QSettings(AUTHOR_NAME, APP_NAME);
    ClearCore *clearCore = new ClearCore();

    layout->addWidget(clearButton, 0, 2);

    // clang-format off
    connect(clearButton, &QPushButton::clicked, [this, table, clearCore]() {  
        struct ClearCoreParams params {
            .table = table,
            .button = clearButton,
            .settings = settings,
        };
        clearCore->clearCache(params);
    });
}

QPushButton *ClearButton::getClearButton() {
    return clearButton;
}