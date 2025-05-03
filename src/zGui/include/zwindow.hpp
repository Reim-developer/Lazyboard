#ifndef ZWINDOW_HPP
#define ZWINDOW_HPP
#include <QMainWindow>
#include <QIcon>
#include <QGridLayout>
#include <QWidget>
#include "ztable.hpp"

namespace zclipboard::zgui {
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
    };
} // namespace zlipboard::zgui

#endif // ZWINDOW_HPP