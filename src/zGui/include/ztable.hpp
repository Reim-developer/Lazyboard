#ifndef ZTABLE_HPP 
#define ZTABLE_HPP
#include <QWidget>
#include <QGridLayout>
#include <QTableWidget>
#include <QObject>
#include <QClipboard>
#include <QDialog>
#include <QIcon>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QSet>
#include <QString>
#include "zdialog.hpp"
#include "../../zSQL/include/zSQL.hpp"
#define CONTENT_COLUMN 1

using namespace zclipboard::zSQL;

namespace zclipboard::zGui {
    class ZTable : public QObject {
        Q_OBJECT

        public:
            ZTable();
            
            QTableWidget *ztableWidget;
            void addZtable(QWidget *zWindow, QGridLayout *zLayout);

        private:
            QClipboard *zClipboard;
            QSet<QString> zExistingContents;
            QSet<QString> zExistingImages;
            
            zManagerSQL zSQLManager;
            ZDialog *zDialog;
            
        public slots:
        void onContentClicked(QTableWidgetItem *ztableWidgetItem);
    };
} // namespace zclipboard::gui

#endif 