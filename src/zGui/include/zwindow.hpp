#ifndef ZWINDOW_HPP
#define ZWINDOW_HPP
#include <QMainWindow>
#include <QIcon>
#include <QGridLayout>
#include <QWidget>
#include <QString>
#include <QSystemTrayIcon>
#include <QStringLiteral>
#include <QMenu>
#include "ztable.hpp"
#include "zSearchPanel.hpp"
#include "clearButton.hpp"
#include "getButton.hpp"
#include "settingButton.hpp"
#include "disconnectButton.hpp"
#include "systemTray.hpp"
#include <QSettings>

using zclipboard::zGui::ClearButton;
using zclipboard::zGui::GetButton;
using zclipboard::zGui::SearchArea;
using zclipboard::zGui::SettingButton;
using zclipboard::zGui::SystemTray;

namespace zclipboard::zGui {

struct AppConfig {
    inline static constexpr int Z_WINDOW_WIDTH = 800;
    inline static constexpr int Z_WINDOW_HEIGHT = 600;
};

class ZWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit ZWindow(QWidget *zWindow = nullptr);
    void loadTranslator();

   private:
    void setupGui();
    void createSystemTray();
    void addTrayMenuActions(QSystemTrayIcon *trayIcon);
    void translatorDectect();

   protected:
    void closeEvent(QCloseEvent *event) override;

   private:
    QSettings *settings;
    QIcon zIcon;
    QWidget *zCentralWidget;
    QGridLayout *zLayout;
    SystemTray *systemTray;

    ZTable *ztable;
    SearchArea *zSearchArea;

    ClearButton *clearButton;
    GetButton *getButton;
    SettingButton *settingButton;
    DisconnectButton *disconnectButton;
};
}  // namespace zclipboard::zGui

#endif  // ZWINDOW_HPP