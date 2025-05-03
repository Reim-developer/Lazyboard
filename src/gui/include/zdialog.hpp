#ifndef ZDIALOG_HPP
#define ZDIALOG_HPP
#include <QDialog>
#include <QString>
#include <QObject>
#include <QTableWidget>

namespace zclipboard::zgui {
    class ZDialog : public QObject {
        Q_OBJECT

        public:
            void showZContentDialog(const QString &text, QTableWidget *ztableWidget);
    };
}

#endif 