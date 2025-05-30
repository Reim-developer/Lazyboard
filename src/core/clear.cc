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

    if (QFile(cachePath).exists()) {
        QFile(cachePath).remove();
    }

    /* Flag for debug only.
    * Usage with CMake flag:
    * -DZ_DEBUG=1
    */
    // clang-format off
    #if defined(Z_DEBUG)
        params.table->getZSQL().resetConnection();
        qDebug() << "Close database successfully";  
                   
    #else
        params.table->getZSQL().resetConnection();
    #endif
    // clang-format on

    QSqlDatabase::removeDatabase(DB_NAME);

    // clang-format off
    const auto function_initDB = [table = params.table]() { 
        table->getZSQL().setupinitDB(); 
    };
    // clang-format on

    QTimer::singleShot(500, function_initDB);

    // clang-format off
    const int LANGUAGE_TYPE = params.settings->value(LANGUAGE_SETTING).toInt();
    const auto BUTTON_TEXT = LANGUAGE_TYPE ? CLEAR_HISTORY_VI : CLEAR_HISTORY_EN;
    const auto ACTION_BUTTON_TEXT = LANGUAGE_TYPE ? CLEAR_HISTORY_ACTION_VI : CLEAR_HISTORY_ACTION_EN;
    // clang-format on

    params.button->setText(ACTION_BUTTON_TEXT);

    const auto function_setText = [clearButton = params.button, BUTTON_TEXT]() {
        clearButton->setText(BUTTON_TEXT);
    };

    QTimer::singleShot(1500, function_setText);
}