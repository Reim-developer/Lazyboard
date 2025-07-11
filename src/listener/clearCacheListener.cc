#include "include/clearCacheListener.hpp"
#include "../zUtils/include/zUtils.hpp"
#include "../language/include/language.hpp"
#include "../zUtils/include/settings.hpp"
#include <QTimer>
#include <QFile>
#include <functional>
#define C_STR(var_name) const char var_name[]

using zclipboard::listener::ClearCacheListener;
using zclipboard::listener::ListenerCache;

ClearCacheListener *ClearCacheListener::StartBuild() {
    cache = MakePtr<ListenerCache>();

    return this;
}

const auto LanguageTypeLambda = [](QSettings *settings) -> int {
    const int LANGUAGE_TYPE = 
        settings
            ->  value(LANGUAGE_SETTING)
            .   toInt();

    return LANGUAGE_TYPE;
};

function<void(ZTable *table)> InitDatabaseFunc = [](ZTable *table) {
    table
        ->  getZSQL()
        .   setupinitDB();
};

function<void(QPushButton *button, C_STR(str))> SetButtonTextFunc = [](QPushButton *button, C_STR(str)) {
    button
        ->  setText(str);
};

function<void(ListenerCache *cache)> ClearDatabaseFunc = [](ListenerCache *cache) -> void {
      /* Flag for debug only.
        * Usage with CMake flag:
        * -DZ_DEBUG=1
        */

        #if defined(Z_DEBUG)
                cache
                ->  table
                ->  getZModel()
                ->  clearData();

                cache
                ->  table
                ->  getZSQL()
                .   resetConnection();

            qDebug() << "Close database successfully";  
                    
        #else
                cache
                ->  table
                ->  getZModel()
                ->  clearData();

                cache
                ->  table
                ->  getZSQL()
                .   resetConnection();
        #endif
};


function<void()> ClearCacheListener::TryGetListener() {
    const auto function = [this]() -> void {
        const constexpr char DB_FILE[] = "zclipboard.db";
        const constexpr char DB_NAME[] = "ZClipboardDB";
        const auto cachePath = zUtils::getCachePath() + "/" + DB_FILE;

        if (QFile(cachePath).exists()) {
            QFile(cachePath).remove();
        }
  
        ClearDatabaseFunc(
            this
                ->  cache
                .   get()
        );
        QSqlDatabase::removeDatabase(DB_NAME);  
        QTimer::singleShot(500,[this]() {
            InitDatabaseFunc(
                this
                    ->  cache
                    ->  table
            );
        });

        const int LANGUAGE_TYPE = LanguageTypeLambda(
            this 
                ->  cache
                ->  settings   
        );

        const auto BUTTON_TEXT = LANGUAGE_TYPE ? CLEAR_HISTORY_VI : CLEAR_HISTORY_EN;
        const auto ACTION_BUTTON_TEXT = LANGUAGE_TYPE ? CLEAR_HISTORY_ACTION_VI : CLEAR_HISTORY_ACTION_EN;

        this
            ->  cache
            ->  button
            ->  setText(ACTION_BUTTON_TEXT);

            QTimer::singleShot(1500, [this, BUTTON_TEXT]() {
                auto button = this
                    ->  cache
                    ->  button;

                SetButtonTextFunc(button, BUTTON_TEXT);
            });
        };

    return function;
}