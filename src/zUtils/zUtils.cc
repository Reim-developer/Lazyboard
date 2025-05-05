#include "include/zUtils.hpp"
#include <QtCoreGlobal>
#include <QStandardPaths>

using namespace zclipboard;

QString zUtils::getCachePath() {
#ifdef Q_OS_WIN
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
#else
    return QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
#endif
}