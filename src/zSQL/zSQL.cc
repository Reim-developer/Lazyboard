#include "include/zSQL.hpp"
#include "../zUtils/include/zUtils.hpp"
#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QVariantMap>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <memory>

using zclipboard::zSQL::zManagerSQL;
using namespace zclipboard;
using std::make_unique;

zManagerSQL::zManagerSQL() {
    zInitCache();
}

void zManagerSQL::zInitCache() {
    QDir qDir;
    QString cachePath = zUtils::getCachePath();

    if (!qDir.exists(cachePath)) qDir.mkdir(cachePath);
}

void zManagerSQL::setupinitDB() {
    QString dbPath = zUtils::getCachePath() + "/" + DATABASE_FILE;
    QDir directory;

    if (!directory.exists(dbPath)) directory.mkpath(zUtils::getCachePath());

    if (!QSqlDatabase::contains(Z_DB_NAME)) {
        zDB = QSqlDatabase::addDatabase(SQL_TYPE, Z_DB_NAME);
        zDB.setDatabaseName(dbPath);

    } else {
        zDB = QSqlDatabase::database(Z_DB_NAME);
    }

    if (!zDB.isOpen()) zDB.open();

    QSqlQuery sqlQuery(zDB);
    sqlQuery.exec(QStringLiteral(R"(
         CREATE TABLE IF NOT EXISTS clipboard (
            time TEXT, content TEXT,
            content_hash TEXT PRIMARY KEY,
            length INTEGER,
            image_data BLOB,
            is_pinned INTEGER DEFAULT 0
        )    
    )"));
}

void zManagerSQL::executeQuery(const QString &sql, const QVariantMap &params) const {
    QSqlQuery sqlQuery(zDB);
    sqlQuery.prepare(sql);

    for (auto it = params.begin(); it != params.end(); it++)
        sqlQuery.bindValue(":" + it.key(), it.value());

    sqlQuery.exec();
}

unique_ptr<QSqlQuery> zManagerSQL::executeQueryResult(const QString &sql,
                                                      const QVariantMap &params) const {
    auto sqlQuery = make_unique<QSqlQuery>(zDB);
    sqlQuery->prepare(sql);

    for (auto it = params.begin(); it != params.end(); it++)
        sqlQuery->bindValue(":" + it.key(), it.value());

    sqlQuery->exec();
    return sqlQuery;
}

void zManagerSQL::updatePinStatus(const QString &contentHash, bool isPinned) {
    QSqlQuery sqlQuery = QSqlQuery(zDB);
    sqlQuery.prepare(QStringLiteral(R"(
            UPDATE clipboard
            SET is_pinned = :is_pinned
            WHERE content_hash = :content_hash
    )"));

    sqlQuery.bindValue(":content_hash", contentHash);
    sqlQuery.bindValue(":is_pinned", isPinned ? 1 : 0);

    if (!sqlQuery.exec()) {
        qDebug() << sqlQuery.lastError().text();
    }
}