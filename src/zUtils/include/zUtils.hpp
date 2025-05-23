#ifndef Z_UTILS_HPP
#define Z_UTILS_HPP
#include <QString>
#include <QSystemTrayIcon>
#include "../../language/include/translate.hpp"
#include "../../core/include/enum.hpp"
#include <QWidget>
#include <QObject>
#include <QMimeData>

using zclipboard::core::Platform;
using zclipboard::language::Translate;

namespace zclipboard {
class zUtils : public QObject {
    Q_OBJECT

   public:
    static QString getCachePath();
    static bool getAutoHideSetting();
    static bool getAutoNotificationSetting();
    static int hasPlatform();
    static int hasContentType(const QMimeData *mimeData);
    static Translate::LanguageType languageTypeCast(int value);
    static bool getLanguageSetting();
};
}  // namespace zclipboard

#endif