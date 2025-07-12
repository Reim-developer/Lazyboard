#ifndef CORE_SYSTEM_TRAY_HPP
#define CORE_SYSTEM_TRAY_HPP
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QApplication>
#include <QSettings>
#include "../../Utils/Include/Namespace_Macro.hpp"

CORE_NAMESPACE
    struct SystemTrayParams {
        QMainWindow *window;
        QSettings *settings;
        QMenu *trayMenu;
        const int TYPE;
    };
    class SystemTrayCore : public QObject {
        Q_OBJECT

    public:
        void updateSwitchLanguageInstance(const SystemTrayParams &params);
        void translatorDectect(const SystemTrayParams &params);

    private:
        void loadTranslator(const SystemTrayParams &params);
    };
END_NAMESPACE

#endif  // CORE_SYSTEM_TRAY_HPP