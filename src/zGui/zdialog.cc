#include "include/zdialog.hpp"
#include <QPointer>
#include <QGridLayout>
#include <QPushButton>
#include <QIcon>
#include <QPlainTextEdit>
#include <QApplication>
#include <QClipboard>
#include <QTimer>
#include <QScrollArea>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QPointer>
#include <QBuffer>
#include <QStringLiteral>
#include <QMessageBox>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include "../znetwork/include/PeerDialog.hpp"
#include "../znetwork/include/PeerDiscovery.hpp"

using zclipboard::zGui::ZDialog;
using zclipboard::znetwork::PeerDialog;
using zclipboard::znetwork::PeerDiscovery;

void ZDialog::showZContentDialog(const QString &text, QTableView *zTableView) {
    auto *zContentDialog = new QDialog(zTableView);
    QIcon zIcon = QIcon(QStringLiteral(":/assets/assets/icon.png"));
    auto *zDialogLayout = new QGridLayout(zContentDialog);

    auto *zContentArea = new QPlainTextEdit(zContentDialog);
    auto *zCopyButton = new QPushButton(zContentDialog);
    auto *sendToDeviceButton = new QPushButton(zContentDialog);

    zContentDialog->setWindowTitle(QStringLiteral("zContent Clipboard"));
    zContentDialog->resize(DIALOG_WIDTH_BASE, DIALOG_HEIGHT_BASE);
    zContentDialog->setWindowIcon(zIcon);

    zContentArea->setReadOnly(true);
    zContentArea->setPlainText(text);
    zContentArea->setLineWrapMode(QPlainTextEdit::NoWrap);

    zCopyButton->setText("Copy Content");
    zCopyButton->setIcon(QIcon::fromTheme(QStringLiteral("edit-copy")));

    sendToDeviceButton->setText(QStringLiteral("Send clipboard to device"));

    connect(sendToDeviceButton, &QPushButton::clicked,
            [this, zContentDialog]() { showPeerListDialog(zContentDialog); });

    QPointer<QPushButton> safeCopyButton = zCopyButton;
    connect(zCopyButton, &QPushButton::clicked,
            [safeCopyButton, text, this] { saveTextToClipboard(safeCopyButton, text); });

    zDialogLayout->addWidget(zCopyButton, 1, 0);
    zDialogLayout->addWidget(sendToDeviceButton, 1, 1);
    zDialogLayout->addWidget(zContentArea, 0, 0, 1, 2);

    zContentDialog->setAttribute(Qt::WA_DeleteOnClose);
    zContentDialog->exec();
}

void ZDialog::showZImageDialog(const QImage &image, QWidget *parent) {
    auto *zDialog = new QDialog(parent);
    auto *saveButton = new QPushButton(zDialog);
    auto *scrollArea = new QScrollArea(zDialog);
    auto *zLayout = new QGridLayout(zDialog);
    auto *imageLabel = new QLabel(zDialog);

    zDialog->setWindowTitle(QStringLiteral("zClipboard Image Viewer"));
    zDialog->resize(DIALOG_WIDTH_BASE, DIALOG_HEIGHT_BASE);

    QPixmap pixmap = QPixmap::fromImage(image);
    QSize maxSize = zDialog->size() * 0.9;
    QPixmap scaledPixmap = pixmap.scaled(maxSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    imageLabel->setPixmap(scaledPixmap);
    imageLabel->adjustSize();
    imageLabel->setAlignment(Qt::AlignCenter);

    scrollArea->setWidget(imageLabel);
    scrollArea->setWidgetResizable(false);

    saveButton->setText("Save Image");
    QPointer<QPushButton> safeButton = saveButton;

    connect(saveButton, &QPushButton::clicked,
            [safeButton, zDialog, image, this]() { saveImage(safeButton, zDialog, image); });

    zLayout->addWidget(scrollArea, 0, 0);
    zLayout->addWidget(saveButton, 1, 0);

    zDialog->setAttribute(Qt::WA_DeleteOnClose);
    zDialog->setLayout(zLayout);
    zDialog->exec();
}

void ZDialog::saveImage(QPointer<QPushButton> safeButton, QDialog *parent, const QImage &image) {
    QString fileName = QFileDialog::getSaveFileName(parent, "Save as", QString(),
                                                    "Images (*.png *.xpm *.jpg *.bmp)");

    if (!fileName.isEmpty()) {
        QFileInfo fileInfo(fileName);
        if (fileInfo.suffix().isEmpty()) fileName += ".png";

        bool isSuccess = image.save(fileName);

        if (isSuccess) {
            if (safeButton) safeButton->setText("Image Saved!");

            QTimer::singleShot(1500, [=]() {
                if (safeButton) safeButton->setText("Save Image");
            });

        } else {
            QMessageBox::critical(parent, "Error", "Failed to save image!");
            if (safeButton) safeButton->setText("Save Image");
        }
    }
}

void ZDialog::saveTextToClipboard(QPointer<QPushButton> safeButton, const QString &text) {
    QApplication::clipboard()->setText(text);

    if (safeButton) {
        safeButton->setText("Copied!");

        QTimer::singleShot(1500, [safeButton]() {
            if (safeButton) safeButton->setText("Copy Content");
        });
    }
}

void ZDialog::showPeerListDialog(QDialog *parent) {
    PeerDialog *peerDialog = new PeerDialog(parent);
    PeerDiscovery *discovery = new PeerDiscovery(45454, peerDialog);

    connect(discovery, &PeerDiscovery::peerFound, [&peerDialog](const QString &ip) {
        if (!peerDialog->getPeerList()->findItems(ip, Qt::MatchExactly).isEmpty()) return;

        peerDialog->getPeerList()->addItem(ip);
    });

    peerDialog->setAttribute(Qt::WA_DeleteOnClose);
    peerDialog->exec();
}
