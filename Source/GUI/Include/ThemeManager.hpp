#ifndef THEME_MANAGER_HPP
#define THEME_MANAGER_HPP
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
        void OnThemeChanged(const int THEME);

    private:
        explicit ThemeManager(QObject *parent = nullptr);
        QSettings *settings;
    };

END_NAMESPACE

#endif  // THEME_MANAGER_HPP