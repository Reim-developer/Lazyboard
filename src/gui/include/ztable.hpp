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
#define CONTENT_COLUMN 1

namespace zclipboard::zgui {
    class ZTable : public QObject {
        Q_OBJECT

        public:
            QTableWidget *ztableWidget;
            void addZtable(QWidget *zWindow, QGridLayout *zLayout);

        private:
            QClipboard *zClipboard;
            QSet<QString> zExistingContents;
            
            void addClipboardHistory();
            void showZContentDialog(const QString &text);
        
        public slots:
        void onContentClicked(QTableWidgetItem *ztableWidgetItem);
        void onCopyButtonClicked();

    };
} // namespace zclipboard::gui

#endif 