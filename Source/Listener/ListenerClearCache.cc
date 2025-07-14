#include "Include/ListenerClearCache.hpp"
#include "../Utils/Include/Utils.hpp"
#include "../Language/Include/Language.hpp"
#include "../Utils/Include/Settings.hpp"
#include <QTimer>
#include <QFile>
#include <functional>
#define C_STR(var_name) const char var_name[]

using ZClipboard::Listener::ClearCacheListener;
using ZClipboard::Listener::ListenerCacheImpl;
using ZClipboard::AppUtils::Utils;

const auto LanguageTypeLambda = [](QSettings *settings) -> int {
    const int LANGUAGE_TYPE = 
        settings
            ->  value(LANGUAGE_SETTING)
            .   toInt();

    return LANGUAGE_TYPE;
};

function<void(TableView *table)> InitDatabaseFunc = [](TableView *table) {
    table
        ->  GetDatabase()
        .   setupinitDB();
};

function<void(QPushButton *button, C_STR(str))> SetButtonTextFunc = [](QPushButton *button, C_STR(str)) {
    button
        ->  setText(str);
};

function<void(ListenerCacheImpl *Impl)> ClearDatabaseFunc = [](ListenerCacheImpl *Impl) -> void {
      /* Flag for debug only.
        * Usage with CMake flag:
        * -DZ_DEBUG=1
        */

        #if defined(Z_DEBUG)
                Impl
                ->  table
                ->  GetTableModel()
                ->  clearData();

                Impl
                ->  table
                ->  GetDatabase()
                .   resetConnection();

            qDebug() << "Close database successfully";  
                    
        #else
                Impl
                ->  table
                ->  GetTableModel()
                ->  clearData();

                Impl
                ->  table
                ->  GetDatabase()
                .   resetConnection();
        #endif
};


VOID_FUNC ClearCacheListener::TryGetListener() {
    const auto function = [this]() -> void {
        const constexpr char DB_FILE[] = "zclipboard.db";
        const constexpr char DB_NAME[] = "ZClipboardDB";
        const auto cachePath = Utils::getCachePath() + "/" + DB_FILE;

        if (QFile(cachePath).exists()) {
            QFile(cachePath).remove();
        }
  
        ClearDatabaseFunc(
            this
                ->  Impl
                .   get()
        );
        QSqlDatabase::removeDatabase(DB_NAME);  
        QTimer::singleShot(500,[this]() {
            InitDatabaseFunc(
                this
                    ->  Impl
                    ->  table
            );
        });

        const int LANGUAGE_TYPE = LanguageTypeLambda(
            this 
                ->  Impl
                ->  settings   
        );

        const auto BUTTON_TEXT = LANGUAGE_TYPE ? CLEAR_HISTORY_VI : CLEAR_HISTORY_EN;
        const auto ACTION_BUTTON_TEXT = LANGUAGE_TYPE ? CLEAR_HISTORY_ACTION_VI : CLEAR_HISTORY_ACTION_EN;

        this
            ->  Impl
            ->  button
            ->  setText(ACTION_BUTTON_TEXT);

            QTimer::singleShot(1500, [this, BUTTON_TEXT]() {
                auto button = this
                    ->  Impl
                    ->  button;

                SetButtonTextFunc(button, BUTTON_TEXT);
            });
        };

    return function;
}