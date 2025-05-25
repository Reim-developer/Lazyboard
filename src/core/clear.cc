#include "include/clear.hpp"
#include <QTimer>
#include <QFile>
#include <QtSql/QSqlDatabase>
#include "../zUtils/include/settings.hpp"
#include "../language/include/language.hpp"
#include "../zUtils/include/zUtils.hpp"

using zclipboard::core::ClearCore;

void ClearCore::clearCache(const ClearCoreParams &params) {
    const constexpr char DB_FILE[] = "zclipboard.db";
    const constexpr char DB_NAME[] = "ZClipboardDB";
    const auto cachePath = zUtils::getCachePath() + "/" + DB_FILE;

    QSqlDatabase database = QSqlDatabase::database(DB_NAME);
    if (database.isOpen()) {
        database.close();
    }

    if (QFile(cachePath).exists()) {
        QFile(cachePath).remove();
    }
    params.table->getZSQL().setupinitDB();

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