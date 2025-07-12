#ifndef THEME_MANAGER
#define THEME_MANAGER
#include <QObject>
#include <QSettings>
#include "../../Utils/Include/Namespace_Macro.hpp"

GUI_NAMESPACE

    class ThemeManager : public QObject {
        Q_OBJECT

    public:
        static ThemeManager &instance();
        void setTheme(const int THEME);

    signals:
        void themeChanged(const int THEME);

    private:
        explicit ThemeManager(QObject *parent = nullptr);
        QSettings *settings;
    };

END_NAMESPACE

#endif  // THEME_MANAGER