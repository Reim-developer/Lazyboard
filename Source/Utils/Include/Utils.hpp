#ifndef Z_UTILS_HPP
#define Z_UTILS_HPP
#include <QString>
#include <QSystemTrayIcon>
#include "../../Language/Include/Translate.hpp"
#include "../../Core/Include/Enum.hpp"
#include "Meta_Macro.hpp"
#include "../../Lib_Memory/Include/Memory.hpp"
#include "Namespace_Macro.hpp"
#include "Meta_Macro.hpp"
#include <QWidget>
#include <QObject>
#include <QMimeData>
#include <utility>

#if defined(Z_DEBUG)
    #include <source_location>
#endif

using ZClipboard::Core::ContentType;
using ZClipboard::Core::Platform;
using ZClipboard::Language::Translate;
using ZClipboard::Lib_Memory::MakePtr;
using std::forward;
using std::string;

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
        struct LogContext {
            const std::source_location &location = std::source_location::current();

            template<typename... Args>
            void LogDebug(Args&&... args) {
                #if defined (Z_DEBUG)
                    auto debugStream = qDebug().noquote();

                    debugStream << " [DEBUG_MODE] In File:" << location.file_name()<< "\n";
                    debugStream << "[DEBUG_MODE] In Function:" << location.function_name() << "\n";
                    debugStream << "[DEBUG_MODE] In Line:" << location.line() << "\n";
                    debugStream << "[DEBUG_MODE] Address:";
                    (debugStream << ... << args);
                    debugStream << "\n";
                #endif
            }
        };

        /*
        * Initiation a smart pointer.
        */
        template<typename T, typename V, typename... Args>
        static void MakeSmartPtr(V &&value, Args&&... args) {
            #if !defined (_WIN32)

                if(!value) {
                    MAKE_SMART_PTR(T, value, (std::forward<Args>(args)...));
                }

            #else

                if(!value) {
                    value = MakePtr<T>(std::forward<Args>(args)...);
                }

            #endif
        }

        
    };

END_NAMESPACE

#endif