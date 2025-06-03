#ifndef Z_UTILS_HPP
#define Z_UTILS_HPP
#include <QString>
#include <QSystemTrayIcon>
#include "../../language/include/translate.hpp"
#include "../../core/include/enum.hpp"
#include <QWidget>
#include <QObject>
#include <QMimeData>

using zclipboard::core::ContentType;
using zclipboard::core::Platform;
using zclipboard::language::Translate;

namespace zclipboard {
class zUtils : public QObject {
    Q_OBJECT

   public:
    static QString getCachePath();
    static Platform hasPlatform();
    static bool hasSetting(const char* SETTING_NAME);
    static ContentType hasContentType(const QMimeData* mimeData);
    static Translate::LanguageType languageTypeCast(int value);
};
}  // namespace zclipboard

#endif