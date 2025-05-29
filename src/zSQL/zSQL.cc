#include "include/zSQL.hpp"
#include "../zUtils/include/zUtils.hpp"
#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QVariantMap>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
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

    if (!qDir.exists(cachePath)) {
        qDir.mkdir(cachePath);
    }
}

void zManagerSQL::setupinitDB() {
    const QString DATABASE_PATH = zUtils::getCachePath() + "/" + DATABASE_FILE;
    QDir directory;

    if (!directory.exists(DATABASE_PATH)) {
        directory.mkpath(zUtils::getCachePath());
    }

    zDB = QSqlDatabase::addDatabase(SQL_TYPE, Z_DB_NAME);
    zDB.setDatabaseName(DATABASE_PATH);

    if (!zDB.isOpen()) {
        if (!zDB.open()) {
            qDebug() << "Error in class zManagerSQL: " << zDB.lastError().text();
        }
    }

    QSqlQuery sqlQuery(zDB);

    if (!sqlQuery.exec(QStringLiteral(R"(
         CREATE TABLE IF NOT EXISTS clipboard (
            time TEXT, content TEXT,
            content_hash TEXT PRIMARY KEY,
            length INTEGER,
            image_data BLOB,
            is_pinned INTEGER DEFAULT 0
        )    
    )"))) {
        qDebug() << "Error in 'exec', function: 'setupinitDB'";
    }
}

void zManagerSQL::executeQuery(const QString &sql, const QVariantMap &params) const {
    QSqlQuery sqlQuery(zDB);
    sqlQuery.prepare(sql);

    for (auto it = params.begin(); it != params.end(); it++) {
        sqlQuery.bindValue(":" + it.key(), it.value());
    }

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

    sqlQuery.exec();
}
