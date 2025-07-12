#include "Include/NetworkDialog.hpp"
#include <QStringLiteral>
#include <QGridLayout>
#include <QSizePolicy>
#include <QtNetwork/QTcpSocket>
#include <QApplication>
#include <QMessageBox>
#include <QClipboard>

using ZClipboard::Network::PeerDialog;

PeerDialog::PeerDialog(const QString &clipboardContent, QWidget *parent)
    : QDialog(parent), m_clipboardContent(clipboardContent) {
    setWindowTitle(QStringLiteral("Select Device"));
    resize(DIALOG_WIDTH_BASE, DIALOG_HEIGHT_BASE);

    peerList = new QListWidget(this);
    sendButton = new QPushButton(this);
    layout = new QGridLayout(this);
    infoLabel = new QLabel(this);
    emptyLabel = new QLabel(this);
    stackContainer = new QWidget(this);
    stackedLayout = new QStackedLayout(stackContainer);

    peerList->setSelectionMode(QAbstractItemView::SingleSelection);

    sendButton->setText(QStringLiteral("Send to selected device"));
    infoLabel->setText(QStringLiteral("Devices in LAN:"));
    emptyLabel->setText(QStringLiteral(R"(
       Nothing to show. 
       Ensure the target device has ZClipboard installed,
       and is ready to receive your clipboard content.
    )"));

    emptyLabel->setWordWrap(true);
    emptyLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    emptyLabel->setMinimumSize(500, 100);
    emptyLabel->setAlignment(Qt::AlignCenter);
    emptyLabel->hide();

    sendButton->setEnabled(!peerList->selectedItems().isEmpty());

    stackedLayout->setContentsMargins(0, 0, 0, 0);
    stackedLayout->addWidget(peerList);
    stackedLayout->addWidget(emptyLabel);

    layout->addWidget(infoLabel, 0, 0);
    layout->addWidget(stackContainer, 1, 0);
    layout->addWidget(sendButton, 2, 0);

    connect(peerList, &QListWidget::itemSelectionChanged,
            [this]() { sendButton->setEnabled(!peerList->selectedItems().isEmpty()); });

    connect(peerList->model(), &QAbstractItemModel::rowsInserted, this,
            &PeerDialog::updateEmptyState);
    connect(peerList->model(), &QAbstractItemModel::rowsRemoved, this,
            &PeerDialog::updateEmptyState);

    connect(sendButton, &QPushButton::clicked, this, [this]() {
        QTcpSocket *socket = new QTcpSocket(this);
        syncClipboard(socket);
    });

    setLayout(layout);
    updateEmptyState();
}

void PeerDialog::syncClipboard(QTcpSocket *socket) {
    QList<QListWidgetItem *> selected = peerList->selectedItems();

    QString deviceIP = selected.first()->text();
    QStringList parts = deviceIP.split('|');
    const QString ipAddress = parts[0];

    connect(socket, &QTcpSocket::connected, [this, socket]() {
        if (socket->write(m_clipboardContent.toUtf8()) == -1) {
            QMessageBox::critical(this, "Error", "Failed to send clipboard.");

        } else {
            QMessageBox::information(this, "Success", "Clipboard sent!");
        }
        socket->flush();
        socket->disconnectFromHost();
    });

    socket->connectToHost(ipAddress, 8000);
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
