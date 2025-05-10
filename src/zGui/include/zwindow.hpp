#ifndef ZWINDOW_HPP
#define ZWINDOW_HPP
#include <QMainWindow>
#include <QIcon>
#include <QGridLayout>
#include <QWidget>
#include <QString>
#include "ztable.hpp"
#include "zSearchPanel.hpp"
#include "clearButton.hpp"

using zclipboard::zGui::ClearButton;
using zclipboard::zGui::SearchArea;

namespace zclipboard::zGui {
class ZWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit ZWindow(QWidget *zWindow = nullptr);

   private:
    void setupGui();

   private:
    QIcon zIcon;
    QWidget *zCentralWidget;
    QGridLayout *zLayout;

    ZTable *ztable;
    SearchArea *zSearchArea;
    ClearButton *clearButton;

   private:
    inline static constexpr int Z_WINDOW_WIDTH = 800;
    inline static constexpr int Z_WINDOW_HEIGHT = 600;
};
}  // namespace zclipboard::zGui

#endif  // ZWINDOW_HPP