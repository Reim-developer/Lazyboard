#include "include/zUtils.hpp"
#include <QtGlobal>
#include <QStandardPaths>

using namespace zclipboard;

QString zUtils::getCachePath() {
#ifdef Q_OS_WIN
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
#else
    return QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
#endif
}