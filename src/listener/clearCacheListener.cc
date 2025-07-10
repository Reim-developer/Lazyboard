#include "include/clearCacheListener.hpp"
#include "../zUtils/include/zUtils.hpp"
#include "../language/include/language.hpp"
#include "../zUtils/include/settings.hpp"
#include <QTimer>
#include <QFile>

using zclipboard::listener::ClearCacheListener;

ClearCacheListener *ClearCacheListener::StartBuild() {
    cache = MakePtr<ListenerCache>();

    return this;
}

function<void()> ClearCacheListener::TryGetListener() {
    const auto function = [this]() -> void {
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

    #if defined(Z_DEBUG)
        this
            ->cache
            ->table
            ->getZSQL().resetConnection();
        qDebug() << "Close database successfully";  
                   
    #else
        this
            ->cache
            ->table
            ->getZSQL().resetConnection();
    #endif

    QSqlDatabase::removeDatabase(DB_NAME);

    const auto function_initDB = [this]() { 
        this
            ->cache
            ->table
            ->getZSQL().setupinitDB(); 
    };


    QTimer::singleShot(500, function_initDB);

    const int LANGUAGE_TYPE = this
        ->cache
        ->settings
        ->value(LANGUAGE_SETTING).toInt();

    const auto BUTTON_TEXT = LANGUAGE_TYPE ? CLEAR_HISTORY_VI : CLEAR_HISTORY_EN;
    const auto ACTION_BUTTON_TEXT = LANGUAGE_TYPE ? CLEAR_HISTORY_ACTION_VI : CLEAR_HISTORY_ACTION_EN;

    this
        ->cache
        ->button
        ->setText(ACTION_BUTTON_TEXT);

    const auto function_setText = [this, BUTTON_TEXT]() {
            this
                ->cache
                ->button
                ->setText(BUTTON_TEXT);
    };

        QTimer::singleShot(1500, function_setText);
    };

    return function;
}