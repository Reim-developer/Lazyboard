#ifndef zSQL_HPP
#define zSQL_HPP
#include <QString>
#include <QVariantMap>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "../../Utils/Include/Namespace_Macro.hpp"

DATABASE_NAMESPACE

    class DatabaseManager {
    public:
        DatabaseManager();

        void setupinitDB();
        void executeQuery(const QString &sql, const QVariantMap &params = QVariantMap()) const;
        void updatePinStatus(const QString &contentHash, bool isPinned);
        void resetConnection();
        QSqlQuery executeQueryResult(const QString &sql,
                                    const QVariantMap &params = QVariantMap()) const;

    private:
        static const constexpr char Z_DB_NAME[] = "ZClipboardDB";
        static const constexpr char SQL_TYPE[] = "QSQLITE";
        static const constexpr char DATABASE_FILE[] = "zclipboard.db";

        QSqlDatabase zDB;
        void zInitCache();
    };

END_NAMESPACE

#endif