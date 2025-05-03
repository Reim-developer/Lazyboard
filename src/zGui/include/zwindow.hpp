#ifndef ZWINDOW_HPP
#define ZWINDOW_HPP
#include <QMainWindow>
#include <QIcon>
#include <QGridLayout>
#include <QWidget>
#include "ztable.hpp"
#include "zSearchPanel.hpp"

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
    };
} // namespace zlipboard::zgui

#endif // ZWINDOW_HPP