#ifndef THEME_MANAGER
#define THEME_MANAGER
#include <QObject>
#include <QSettings>

namespace zclipboard::zGui {
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
}  // namespace zclipboard::zGui

#endif  // THEME_MANAGER