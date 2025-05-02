#include "include/ztable.hpp"
#include "qheaderview.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QDateTime>
#include <QClipboard>
#include <QApplication>
#include <QTableWidgetItem>

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
    connect(zClipboard, &QClipboard::dataChanged, this, &ZTable::addClipboardHistory);
}

void ZTable::addClipboardHistory() {
        QString text = zClipboard->text();
        if(text.isEmpty()) return;

        const int MAX_CONTENT_LENGTH = 30;

        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        int textLength = text.length();

        int row = ztableWidget->rowCount();
        ztableWidget->insertRow(row);
        ztableWidget->setItem(row, 0, new QTableWidgetItem(time));

       
        ztableWidget->setItem(row, 1, new QTableWidgetItem(text));   
        ztableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(textLength)));
}