#include "include/clear.hpp"
#include <QTimer>
#include "../zUtils/include/settings.hpp"
#include "../language/include/language.hpp"

using zclipboard::core::ClearCore;

void ClearCore::clearCache(const ClearCoreParams &params) {
    QString query = R"(
        DROP TABLE IF EXISTS clipboard
    )";
    params.table->getZSQL().executeQuery(query, QVariantMap());

    // clang-format off
    const int LANGUAGE_TYPE = params.settings->value(LANGUAGE_SETTING).toInt();
    const auto BUTTON_TEXT = LANGUAGE_TYPE ? CLEAR_HISTORY_VI : CLEAR_HISTORY_EN;
    const auto ACTION_BUTTON_TEXT = LANGUAGE_TYPE ? CLEAR_HISTORY_ACTION_VI : CLEAR_HISTORY_ACTION_EN;
    // clang-format on

    params.button->setText(ACTION_BUTTON_TEXT);
    params.table->getZModel()->clearData();

    // clang-format off
    QTimer::singleShot(1500, 
                [clearButton = params.button, BUTTON_TEXT]() { 
                      clearButton->setText(BUTTON_TEXT); 
    });
    // clang-format on
}