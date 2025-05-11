#include "include/PeerDialog.hpp"
#include <QStringLiteral>
#include <QGridLayout>

using zclipboard::znetwork::PeerDialog;

PeerDialog::PeerDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle(QStringLiteral("Select Device"));
    resize(DIALOG_WIDTH_BASE, DIALOG_HEIGHT_BASE);

    peerList = new QListWidget(this);
    sendButton = new QPushButton(this);
    layout = new QGridLayout(this);
    infoLabel = new QLabel(this);
    emptyLabel = new QLabel(this);

    peerList->setSelectionMode(QAbstractItemView::SingleSelection);
    sendButton->setText(QStringLiteral("Send to selected device"));
    sendButton->setEnabled(!peerList->selectedItems().isEmpty());

    infoLabel->setText(QStringLiteral("Devices in LAN:"));

    emptyLabel->setText(QStringLiteral(R"(
        Nothing to show. Make sure device you want send clipboard
        content already install ZClipboard and they want get
        your clipboard content.
    )"));
    emptyLabel->setWordWrap(true);
    emptyLabel->setAlignment(Qt::AlignCenter);
    emptyLabel->hide();

    layout->addWidget(infoLabel, 0, 0);
    layout->addWidget(peerList, 1, 0);
    layout->addWidget(emptyLabel, 1, 0);
    layout->addWidget(sendButton, 2, 0);

    connect(peerList, &QListWidget::itemSelectionChanged,
            [this]() { sendButton->setEnabled(!peerList->selectedItems().isEmpty()); });

    connect(peerList->model(), &QAbstractItemModel::rowsInserted, this,
            &PeerDialog::updateEmptyState);
    connect(peerList->model(), &QAbstractItemModel::rowsRemoved, this,
            &PeerDialog::updateEmptyState);

    setLayout(layout);
    updateEmptyState();
}

QListWidget *PeerDialog::getPeerList() const {
    return peerList;
}

void PeerDialog::updateEmptyState() {
    if (peerList->count() == 0) {
        peerList->hide();
        emptyLabel->show();
    } else {
        peerList->show();
        emptyLabel->hide();
    }
}
