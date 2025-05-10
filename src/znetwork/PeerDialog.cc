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

    peerList->setSelectionMode(QAbstractItemView::SingleSelection);
    sendButton->setText("Send To Selected Device");
    infoLabel->setText("Devices in LAN:");

    layout->addWidget(infoLabel, 0, 0);
    layout->addWidget(peerList, 1, 0);
    layout->addWidget(sendButton, 2, 0);

    connect(peerList, &QListWidget::itemSelectionChanged,
            [this]() { sendButton->setEnabled(!peerList->selectedItems().isEmpty()); });

    setLayout(layout);
}

QListWidget *PeerDialog::getPeerList() const {
    return peerList;
}
