#include "include/ztable.hpp"
#include "include/zdialog.hpp"
#include <QTableWidget>
#include <QHeaderView>
#include <QDateTime>
#include <QClipboard>
#include <QApplication>
#include <QTableWidgetItem>
#include <QtSql/QSqlDatabase>
#include <QTimer>
#include <QPointer>

using namespace zclipboard::zgui;

void ZTable::addZtable(QWidget *zWindow, QGridLayout *zLayout) {
    ztableWidget = new QTableWidget(zWindow);
    ztableWidget->setColumnCount(3);
    
    ztableWidget->setHorizontalHeaderLabels({"Time", "Content", "Content Length"});

    ztableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ztableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ztableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    ztableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    zLayout->addWidget(ztableWidget, 0, 0);

    zClipboard = QApplication::clipboard();
    connect(ztableWidget, &QTableWidget::itemClicked, this, &ZTable::onContentClicked);
    connect(zClipboard, &QClipboard::dataChanged, this, &ZTable::addClipboardHistory);
}

void ZTable::addClipboardHistory() {
        QString text = zClipboard->text();
        if(text.isEmpty()) return;

        if(zExistingContents.contains(text)) return;

        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        int textLength = text.length();

        int row = ztableWidget->rowCount();
        ztableWidget->insertRow(row);
        ztableWidget->setItem(row, 0, new QTableWidgetItem(time));
       
        ztableWidget->setItem(row, 1, new QTableWidgetItem(text));   
        ztableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(textLength)));

        zExistingContents.insert(text);
}

void ZTable::onContentClicked(QTableWidgetItem *ztableWidgetItem) {
    if(ztableWidgetItem->column() != CONTENT_COLUMN) return;

    QString content = ztableWidgetItem->text();
    zDialog = new ZDialog();
    zDialog->showZContentDialog(content, ztableWidget);
}

