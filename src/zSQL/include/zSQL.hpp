#ifndef zSQL_HPP
#define zSQL_HPP
#include <QString>
#include <QVariantMap>
#include <QtSql/QSqlDatabase>
#include <string>
#include <memory>

using std::string;
using std::unique_ptr;

namespace zclipboard::zSQL {
class zManagerSQL {
   public:
    zManagerSQL();

    void setupinitDB();
    void executeQuery(const QString &sql, const QVariantMap &params = QVariantMap());
    void updatePinStatus(const QString &contentHash, bool isPinned);
    unique_ptr<QSqlQuery> executeQueryResult(const QString &sql,
                                             const QVariantMap &params = QVariantMap());

   private:
    const QString Z_DB_NAME = "ZClipboardDB";
    QSqlDatabase zDB;
    void zInitCache();
};
}  // namespace zclipboard::zSQL

#endif