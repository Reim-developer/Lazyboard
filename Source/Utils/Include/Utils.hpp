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