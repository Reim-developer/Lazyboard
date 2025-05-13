#include "include/getButton.hpp"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>

using zclipboard::zGui::GetButton;

void GetButton::addGetButton(QWidget *window, QGridLayout *layout) {
    getButton = new QPushButton(window);
    getButton->setText("Get clipboard from another device");

    connect(getButton, &QPushButton::clicked, this, [this, window]() {
        getButton->setText("Waiting connection device..");
        peer = new PeerDiscovery(45454, window);
    });

    layout->addWidget(getButton, 0, 1);
}