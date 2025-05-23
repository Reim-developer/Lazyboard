#include "include/clearButton.hpp"
#include <QGridLayout>
#include <QPushButton>
#include <QVariant>
#include <QTimer>
#include "include/ztable.hpp"
#include "../zUtils/include/config.hpp"
#include <QSettings>
#include "../zUtils/include/settings.hpp"
#include "../language/include/language.hpp"

using zclipboard::zGui::ClearButton;

void ClearButton::addClearButton(QGridLayout *layout, ZTable *table) {
    clearButton = new QPushButton();
    settings = new QSettings(AUTHOR_NAME, APP_NAME);

    layout->addWidget(clearButton, 0, 2);
    connect(clearButton, &QPushButton::clicked,
            [this, table]() { clearCache(table, clearButton); });
}

void ClearButton::clearCache(ZTable *table, QPushButton *clearButton) {
    QString query = R"(
        DROP TABLE IF EXISTS clipboard
    )";
    table->getZSQL().executeQuery(query, QVariantMap());

    // clang-format off
    const int LANGUAGE_TYPE = settings->value(LANGUAGE_SETTING).toInt();
    const auto BUTTON_TEXT = LANGUAGE_TYPE ? CLEAR_HISTORY_VI : CLEAR_HISTORY_EN;
    const auto ACTION_BUTTON_TEXT = LANGUAGE_TYPE ? CLEAR_HISTORY_ACTION_VI : CLEAR_HISTORY_ACTION_EN;
    // clang-format on

    clearButton->setText(ACTION_BUTTON_TEXT);
    table->getZModel()->clearData();

    QTimer::singleShot(1500, [clearButton, BUTTON_TEXT]() { clearButton->setText(BUTTON_TEXT); });
}

QPushButton *ClearButton::getClearButton() {
    return clearButton;
}