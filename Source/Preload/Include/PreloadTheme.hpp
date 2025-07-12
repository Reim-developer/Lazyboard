#ifndef ZCLIPBOARD_MAIN_HPP
#define ZCLIPBOARD_MAIN_HPP
#include <QApplication>
#include <QObject>
#include "../../Core/Include/Enum.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"

using ZClipboard::Core::Theme;

PRELOAD_NAMESPACE

    class Application : public QObject {
        Q_OBJECT

    private:
        void setDefaultTheme();
        void setDarkTheme(QApplication &application);

        void setLightTheme(QApplication &application);

    public:
        bool loadDefaultTheme();
        void loadSettingTheme(QApplication &application);
        void reloadTheme(const int THEME);
        void onSettingThemeChanged(QApplication &application);

    private:
        static inline const QColor DARK_BG_COLOR {47, 49, 54};
        static inline const QColor DARK_FG_COLOR {255, 255, 255};
        
        static inline const QColor LIGHT_BG_COLOR {255, 255, 255};
        static inline const QColor LIGHT_FG_COLOR {0, 0, 0};

    private:
        static inline const constexpr int THEME_DARK = static_cast<int>(Theme::DARK);
        static inline const constexpr int THEME_LIGHT = static_cast<int>(Theme::LIGHT);
        static inline const constexpr int THEME_SYSTEM = static_cast<int>(Theme::SYSTEM);

        static inline const constexpr char LINUX_DEFAULT_THEME[] = "Fusion";
        static inline const constexpr char WINDOWS_DEFAULT_THEME[] = "Windows";
        static inline const constexpr char MACOS_DEFAULT_THEME[] = "macOS";
    };

END_NAMESPACE

#endif  // ZCLIPBOARD_MAIN_HPP