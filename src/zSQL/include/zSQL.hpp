#ifndef zSQL_HPP
#define zSQL_HPP
#include <QString>
#include <QVariantMap>
#include <QtSql/QSqlDatabase>

namespace zcipboard::zSQL {
    class zSQL {
        public:
            zSQL();

        public:
            void connectToDB();
            void executeQuery(const QString &sql, 
                              const QVariantMap &params = QVariantMap());
            QSqlQuery executeQueryResult(const QString &sql, 
                                         const QVariantMap &params = QVariantMap());

        private:
            QSqlDatabase zDB;
            void zInitCache();
    };
}

#endif 