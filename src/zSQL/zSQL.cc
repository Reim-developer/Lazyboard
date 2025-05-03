#include "include/zSQL.hpp"
#include "../zUtils/include/zUtils.hpp"
#include <QString>
#include <QDir>

using namespace zcipboard::zSQL;
using namespace zclipboard::zUtils;

void zSQL::zInitCache() {
    zUtils *zutils = new zUtils();
    QDir qDir;
    QString cachePath = zutils->getCachePath();

    if(!qDir.exists(cachePath)) qDir.mkdir(cachePath);
}
