#ifndef ZTABLE_HPP 
#define ZTABLE_HPP
#include <QWidget>
#include <QGridLayout>
#include <QTableView>
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
#include "zClipboardModel.hpp"

#define CONTENT_COLUMN 1

using zclipboard::zSQL::zManagerSQL;
using zclipboard::zGui::zTableModel;

namespace zclipboard::zGui {
    class ZTable : public QObject {
        Q_OBJECT

        public:
            ZTable();
            void addZtable(QWidget *zWindow, QGridLayout *zLayout);

        private:
            QClipboard *zClipboard;
            QTableView *zTableView;
            zTableModel *zModelTable;

            QSet<QString> zExistingContents;
            QSet<QString> zExistingImages;
            
            zManagerSQL zSQLManager;
            ZDialog *zDialog;
            
        public slots:
        void onContentClicked(const QModelIndex &current);
    };
} // namespace zclipboard::gui

#endif 