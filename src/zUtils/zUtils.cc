#include "include/zUtils.hpp"
#include <QtSystemDetection>
#include <QStandardPaths>

using namespace zclipboard;

QString zUtils::getCachePath() {
    #ifdef Q_OS_WINDOWS
        return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    #else
        return QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    #endif
}