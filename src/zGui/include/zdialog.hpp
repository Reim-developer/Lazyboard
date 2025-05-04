#ifndef ZDIALOG_HPP
#define ZDIALOG_HPP
#include <QDialog>
#include <QString>
#include <QObject>
#include <QTableWidget>
#include <QTableView>

namespace zclipboard::zGui {
    class ZDialog : public QObject {
        Q_OBJECT

        public:
            void showZContentDialog(const QString &text, QTableView *zTableView);
    };
}

#endif 