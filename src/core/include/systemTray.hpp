#ifndef CORE_SYSTEM_TRAY_HPP
#define CORE_SYSTEM_TRAY_HPP
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QApplication>

namespace zclipboard::core {
struct SystemTrayParams {
    QMenu *trayMenu;
    QMainWindow *window;
    const int &TYPE;
};
class SystemTrayCore : public QObject {
    Q_OBJECT

   public:
    void updateSwitchLanguageInstance(const SystemTrayParams &params);
    void loadTranslator(const SystemTrayParams &params);
};
}  // namespace zclipboard::core

#endif  // CORE_SYSTEM_TRAY_HPP