#ifndef Z_UTILS_HPP
#define Z_UTILS_HPP
#include <QString>
#include <QSystemTrayIcon>
#include "../../language/include/translate.hpp"
#include <QWidget>
#include <QObject>
#include <QMimeData>

using zclipboard::language::Translate;

namespace zclipboard {

// clang-format off
enum class ContentType : int {
    TEXT,
    IMAGE,
    UNKNOWN
};
// clang-format on

class zUtils : public QObject {
    Q_OBJECT

   public:
    static QString getCachePath();
    static bool getAutoHideSetting();
    static bool getAutoNotificationSetting();
    static void textClipboardChanges(QSystemTrayIcon *trayIcon, QClipboard *clipboard);
    static void imageClipboardChanges(QSystemTrayIcon *trayIcon, QClipboard *clipboard);
    static int hasContentType(const QMimeData *mimeData);
    static Translate::LanguageType languageTypeCast(int value);
    static bool getLanguageSetting();
};
}  // namespace zclipboard

#endif