#include "include/zSQL.hpp"
#include "../zUtils/include/zUtils.hpp"
#include <QString>
#include <QVariantMap>
#include <QtSql/QSqlQuery>
#include <QDir>

using namespace zcipboard::zSQL;
using namespace zclipboard::zUtils;

zSQL::zSQL() {
    zInitCache();
}


void zSQL::zInitCache() {
    QDir qDir;
    QString cachePath = zUtils::getCachePath();

    if(!qDir.exists(cachePath)) qDir.mkdir(cachePath);
}

void zSQL::connectToDB() {
    QString dbPath = zUtils::getCachePath() + "/zclipboard.db";

    zDB = QSqlDatabase::addDatabase("QSQLITE", "ZClipboardDB");
    zDB.setDatabaseName(dbPath);
    zDB.open();

    QSqlQuery sqlQuery(zDB);
    sqlQuery.exec(R"(
        --sql
        CREATE TABLE IF NOT EXISTS clipboard (
            time TEXT, content TEXT PRIMARY KEY,
            length INTEGER
        )    
    )");
}

void zSQL::executeQuery(const QString &sql, const QVariantMap &params) {
    QSqlQuery sqlQuery(zDB);
    sqlQuery.prepare(sql);

    for(auto it = params.begin(); it != params.end(); it++)
        sqlQuery.bindValue(":" + it.key(), it.value());

    sqlQuery.exec();
}

QSqlQuery zSQL::executeQueryResult(const QString &sql, const QVariantMap &params) {
    QSqlQuery sqlQuery(zDB);
    sqlQuery.prepare(sql);

    for(auto it = params.begin(); it != params.end(); it++)
        sqlQuery.bindValue(":"+ it.key(), it.value());

    sqlQuery.exec();

    return sqlQuery;
}
