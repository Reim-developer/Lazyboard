#include "include/zSQL.hpp"
#include "../zUtils/include/zUtils.hpp"
#include <QString>
#include <QVariantMap>
#include <QtSql/QSqlQuery>
#include <QDir>

using namespace zclipboard::zSQL;
using namespace zclipboard;

zManagerSQL::zManagerSQL() {
    zInitCache();
}


void zManagerSQL::zInitCache() {
    QDir qDir;
    QString cachePath = zUtils::getCachePath();

    if(!qDir.exists(cachePath)) qDir.mkdir(cachePath);
}

void zManagerSQL::connectToDB() {
    QString dbPath = zUtils::getCachePath() + "/zclipboard.db";

    zDB = QSqlDatabase::addDatabase("QSQLITE", "ZClipboardDB");
    zDB.setDatabaseName(dbPath);
    zDB.open();

    QSqlQuery sqlQuery(zDB);
    sqlQuery.exec(R"(
        --sql
        CREATE TABLE IF NOT EXISTS clipboard (
            time TEXT, content TEXT,
            content_hash TEXT PRIMARY KEY,
            length INTEGER,
            image_data BLOB
        )    
    )");
}

void zManagerSQL::executeQuery(const QString &sql, const QVariantMap &params) {
    QSqlQuery sqlQuery(zDB);
    sqlQuery.prepare(sql);

    for(auto it = params.begin(); it != params.end(); it++)
        sqlQuery.bindValue(":" + it.key(), it.value());

    sqlQuery.exec();
}

QSqlQuery zManagerSQL::executeQueryResult(const QString &sql, const QVariantMap &params) {
    QSqlQuery sqlQuery(zDB);
    sqlQuery.prepare(sql);

    for(auto it = params.begin(); it != params.end(); it++)
        sqlQuery.bindValue(":"+ it.key(), it.value());

    sqlQuery.exec();

    return sqlQuery;
}
