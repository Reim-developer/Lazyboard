#ifndef ZTABLE_HPP 
#define ZTABLE_HPP
#include <QWidget>
#include <QGridLayout>
#include <QTableWidget>
#include <QObject>
#include <QClipboard>

namespace zclipboard::zgui {
    class ZTable : public QObject {
        Q_OBJECT

        public:
            QTableWidget *ztableWidget;
            void addZtable(QWidget *zWindow, QGridLayout *zLayout);

        private:
            QClipboard *zClipboard;
            void addClipboardHistory();

    };
} // namespace zclipboard::gui

#endif 