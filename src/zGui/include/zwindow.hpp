#ifndef ZWINDOW_HPP
#define ZWINDOW_HPP
#include <QMainWindow>
#include <QIcon>
#include <QGridLayout>
#include <QWidget>
#include <QString>
#include <QSystemTrayIcon>
#include <QMenu>
#include "ztable.hpp"
#include "zSearchPanel.hpp"
#include "clearButton.hpp"
#include "getButton.hpp"
#include "settingButton.hpp"

using zclipboard::zGui::ClearButton;
using zclipboard::zGui::GetButton;
using zclipboard::zGui::SearchArea;
using zclipboard::zGui::SettingButton;

namespace zclipboard::zGui {
class ZWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit ZWindow(QWidget *zWindow = nullptr);

   private:
    void setupGui();
    void createTrayIcon();
    void addTrayMenuActions(QSystemTrayIcon *trayIcon);

   protected:
    void closeEvent(QCloseEvent *event) override;

   private:
    QIcon zIcon;
    QWidget *zCentralWidget;
    QGridLayout *zLayout;

    ZTable *ztable;
    SearchArea *zSearchArea;

    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;

    ClearButton *clearButton;
    GetButton *getButton;
    SettingButton *settingButton;

   private:
    inline static constexpr int Z_WINDOW_WIDTH = 800;
    inline static constexpr int Z_WINDOW_HEIGHT = 600;
};
}  // namespace zclipboard::zGui

#endif  // ZWINDOW_HPP