#ifndef Z_UTILS_HPP
#define Z_UTILS_HPP
#include <QString>
#include <QSystemTrayIcon>
#include "../../Language/Include/Translate.hpp"
#include "../../Core/Include/Enum.hpp"
#include "Namespace_Macro.hpp"
#include <QWidget>
#include <QObject>
#include <QMimeData>

using ZClipboard::Core::ContentType;
using ZClipboard::Core::Platform;
using ZClipboard::Language::Translate;

UTILS_NAMESPACE

    class Utils : public QObject {
        Q_OBJECT

    public:
        static QString getCachePath();
        static Platform hasPlatform();
        static bool hasSetting(const char* SETTING_NAME);
        static ContentType hasContentType(const QMimeData* mimeData);
        static Translate::LanguageType languageTypeCast(int value);
        
        /*
        * Only for debug mode is enabled.
        */
        template<typename... Args>
        static void LogDebug(Args&&... args) {
            #if defined (Z_DEBUG)
                auto debugStream = qDebug();
                debugStream << "[DEBUG_MODE]";

                (debugStream << ... << args);
            #endif
        }
    };

END_NAMESPACE

#endif