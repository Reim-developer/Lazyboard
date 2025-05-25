#ifndef zSQL_HPP
#define zSQL_HPP
#include <QString>
#include <QVariantMap>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <string>
#include <memory>

using std::string;
using std::unique_ptr;

namespace zclipboard::zSQL {
class zManagerSQL {
   public:
    zManagerSQL();

    void setupinitDB();
    void resetQueries();
    void executeQuery(const QString &sql, const QVariantMap &params = QVariantMap()) const;
    void updatePinStatus(const QString &contentHash, bool isPinned);
    unique_ptr<QSqlQuery> executeQueryResult(const QString &sql,
                                             const QVariantMap &params = QVariantMap()) const;

   private:
    static const constexpr char Z_DB_NAME[] = "ZClipboardDB";
    static const constexpr char SQL_TYPE[] = "QSQLITE";
    static const constexpr char DATABASE_FILE[] = "zclipboard.db";

    QSqlDatabase zDB;
    void zInitCache();
};
}  // namespace zclipboard::zSQL

#endif