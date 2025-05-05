#ifndef zSQL_HPP
#define zSQL_HPP
#include <QString>
#include <QVariantMap>
#include <QtSql/QSqlDatabase>
#include <memory>
#define Z_DB_NAME "ZClipboardDB"

using std::unique_ptr;

namespace zclipboard::zSQL {
class zManagerSQL {
   public:
    zManagerSQL();

   public:
    void setupinitDB();
    void executeQuery(const QString &sql, const QVariantMap &params = QVariantMap());
    unique_ptr<QSqlQuery> executeQueryResult(const QString &sql, const QVariantMap &params = QVariantMap());

   private:
    QSqlDatabase zDB;
    void zInitCache();
};
}  // namespace zclipboard::zSQL

#endif