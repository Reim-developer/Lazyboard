#ifndef SYSTEM_TRAY_HPP
#define SYSTEM_TRAY_HPP
#include <QSystemTrayIcon>
#include <QWidget>
#include <QObject>
#include <QMainWindow>

namespace zclipboard::zGui {
struct SystemTrayWidget {
    QMainWindow *window;
    QIcon icon;
};
class SystemTray : public QMainWindow {
    Q_OBJECT
   public:
    void addSystemTray(const SystemTrayWidget &widget);
    QSystemTrayIcon *getSystemTrayIcon();

   private:
    void translatorDectect(QMainWindow *window);
    void loadTranslator(QMainWindow *window, const int &TYPE);

    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QAction *showGui;
    QAction *hideGui;
    QAction *quitGui;

   private:
    void addTrayMenuActions(QSystemTrayIcon *systemTrayIcon);
};
}  // namespace zclipboard::zGui

#endif