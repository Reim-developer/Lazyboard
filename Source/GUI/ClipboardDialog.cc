#include "Include/ClipboardDialog.hpp"
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
#include <QSettings>
#include "../Network/Include/NetworkDialog.hpp"
#include "../Network/Include/NetworkDiscovery.hpp"
#include "../Utils/Include/Config.hpp"
#include "../Language/Include/Language.hpp"
#include "../Utils/Include/Settings.hpp"

using ZClipboard::GUI::ClipboardDialog;
using ZClipboard::GUI::ClipboardProperty;
using ZClipboard::Network::PeerDialog;
using ZClipboard::Network::PeerDiscovery;

void ClipboardDialog::showZContentDialog(const QString &text, QTableView *zTableView) {
    auto *zContentDialog = new QDialog(zTableView);
    QIcon zIcon = QIcon(ICON_PATH);
    auto *zDialogLayout = new QGridLayout(zContentDialog);
    QSettings settings(AUTHOR_NAME, APP_NAME);

    const int LANGUAGE_TYPE = settings.value(LANGUAGE_SETTING).toInt();
    const auto DIALOG_TITLE = LANGUAGE_TYPE ? CONTENT_DIALOG_TITLE_VI : CONTENT_DIALOG_TITLE_EN;
    const auto COPY_BUTTON_TEXT = LANGUAGE_TYPE ? COPY_CONTENT_BUTTON_VI : COPY_CONTENT_BUTTON_EN;

    auto *zContentArea = new QPlainTextEdit(zContentDialog);
    auto *zCopyButton = new QPushButton(zContentDialog);
    auto *sendToDeviceButton = new QPushButton(zContentDialog);

    zContentDialog->setWindowTitle(DIALOG_TITLE);
    zContentDialog->resize(DIALOG_WIDTH_BASE, DIALOG_HEIGHT_BASE);
    zContentDialog->setWindowIcon(zIcon);

    zContentArea->setReadOnly(true);
    zContentArea->setPlainText(text);
    zContentArea->setLineWrapMode(QPlainTextEdit::NoWrap);

    zCopyButton->setText(COPY_BUTTON_TEXT);

    const auto SEND_BUTTON_TEXT = LANGUAGE_TYPE ? SEND_CONTENT_BUTTON_VI : SEND_CONTENT_BUTTON_EN;
    sendToDeviceButton->setText(SEND_BUTTON_TEXT);

    connect(sendToDeviceButton, &QPushButton::clicked, [this, zContentDialog, zContentArea]() {
        showPeerListDialog(
            {.parent = zContentDialog, .clipboardContent = zContentArea->toPlainText()});
    });

    QPointer<QPushButton> safeCopyButton = zCopyButton;
    connect(zCopyButton, &QPushButton::clicked, [safeCopyButton, text, this] {
        // clang-format off
        struct ClipboardProperty dialogClipboard {
            .safeButton = safeCopyButton,
            .text = text
        };
        saveTextToClipboard(dialogClipboard);
    });
    // clang-format on

    zDialogLayout->addWidget(zCopyButton, 1, 0);
    zDialogLayout->addWidget(sendToDeviceButton, 1, 1);
    zDialogLayout->addWidget(zContentArea, 0, 0, 1, 2);

    zContentDialog->setAttribute(Qt::WA_DeleteOnClose);
    zContentDialog->exec();
}

void ClipboardDialog::showZImageDialog(const QImage &image, QWidget *parent) {
    auto *zDialog = new QDialog(parent);
    auto *saveButton = new QPushButton(zDialog);
    auto *scrollArea = new QScrollArea(zDialog);
    auto *zLayout = new QGridLayout(zDialog);
    auto *imageLabel = new QLabel(zDialog);
    QSettings settings(AUTHOR_NAME, APP_NAME);

    const int LANGUAGE_TYPE = settings.value(LANGUAGE_SETTING).toInt();

    const auto DIALOG_TITLE = LANGUAGE_TYPE ? IMAGE_DIALOG_TITLE_VI : IMAGE_DIALOG_TITLE_EN;
    zDialog->setWindowTitle(DIALOG_TITLE);
    zDialog->resize(DIALOG_WIDTH_BASE, DIALOG_HEIGHT_BASE);

    QPixmap pixmap = QPixmap::fromImage(image);
    QSize maxSize = zDialog->size() * 0.9;
    QPixmap scaledPixmap = pixmap.scaled(maxSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    imageLabel->setPixmap(scaledPixmap);
    imageLabel->adjustSize();
    imageLabel->setAlignment(Qt::AlignCenter);

    scrollArea->setWidget(imageLabel);
    scrollArea->setWidgetResizable(false);

    const auto BUTTON_TEXT = LANGUAGE_TYPE ? SAVE_IMAGE_BUTTON_VI : SAVE_IMAGE_BUTTON_EN;
    saveButton->setText(BUTTON_TEXT);
    QPointer<QPushButton> safeButton = saveButton;

    connect(saveButton, &QPushButton::clicked, [safeButton, zDialog, image, this]() {
        // clang-format off
        struct ClipboardProperty dialogClipboard {
            .safeButton = safeButton,
            .parent = zDialog,
            .image = image
        };

        saveImage(dialogClipboard);
    });
    // clang-format on

    zLayout->addWidget(scrollArea, 0, 0);
    zLayout->addWidget(saveButton, 1, 0);

    zDialog->setAttribute(Qt::WA_DeleteOnClose);
    zDialog->setLayout(zLayout);
    zDialog->exec();
}

void ClipboardDialog::saveImage(const ClipboardProperty &dialogClipboard) {
    QString fileName = QFileDialog::getSaveFileName(dialogClipboard.parent, "Save as", QString(),
                                                    "Images (*.png *.xpm *.jpg *.bmp)");

    if (!fileName.isEmpty()) {
        QFileInfo fileInfo(fileName);
        if (fileInfo.suffix().isEmpty()) fileName += ".png";

        bool isSuccess = dialogClipboard.image->save(fileName);

        QSettings settings(AUTHOR_NAME, APP_NAME);
        const int LANGUAGE_TYPE = settings.value(LANGUAGE_SETTING).toInt();
        const auto BUTTON_TEXT = LANGUAGE_TYPE ? SAVED_IMAGE_BUTTON_VI : SAVED_IMAGE_BUTTON_EN;

        if (isSuccess) {
            if (dialogClipboard.safeButton) {
                dialogClipboard.safeButton->setText(BUTTON_TEXT);
            }

            QTimer::singleShot(1500, [dialogClipboard, BUTTON_TEXT]() {
                if (dialogClipboard.safeButton) {
                    dialogClipboard.safeButton->setText(BUTTON_TEXT);
                }
            });

        } else {
            const auto DIALOG_ERR_TITLE =
                LANGUAGE_TYPE ? DIALOG_ERROR_TITLE_VI : DIALOG_ERROR_TITLE_EN;
            const auto DIALOG_ERR_MSG = LANGUAGE_TYPE ? SAVE_IMAGE_FAILED_VI : SAVE_IMAGE_FAILED_EN;

            QMessageBox::critical(dialogClipboard.parent, DIALOG_ERR_TITLE, DIALOG_ERR_MSG);

            if (dialogClipboard.safeButton) {
                dialogClipboard.safeButton->setText(BUTTON_TEXT);
            }
        }
    }
}

void ClipboardDialog::saveTextToClipboard(const ClipboardProperty &dialogClipboard) {
    QApplication::clipboard()->setText(dialogClipboard.text.value_or(QStringLiteral("")));

    if (dialogClipboard.safeButton) {
        QSettings settings(AUTHOR_NAME, APP_NAME);

        const int LANGUAGE_TYPE = settings.value(LANGUAGE_SETTING).toInt();
        const auto ALREADY_COPY_TEXT =
            LANGUAGE_TYPE ? ALREADY_COPY_BUTTON_VI : ALREADY_COPY_BUTTON_EN;

        dialogClipboard.safeButton->setText(ALREADY_COPY_TEXT);

        QTimer::singleShot(1500, [dialogClipboard, LANGUAGE_TYPE]() {
            if (dialogClipboard.safeButton) {
                const auto BUTTON_TEXT =
                    LANGUAGE_TYPE ? COPY_CONTENT_BUTTON_VI : COPY_CONTENT_BUTTON_EN;

                dialogClipboard.safeButton->setText(BUTTON_TEXT);
            }
        });
    }
}

void ClipboardDialog::showPeerListDialog(const ClipboardProperty &dialogClipboard) {
    PeerDialog *peerDialog = new PeerDialog(
        dialogClipboard.clipboardContent.value_or(QStringLiteral("")), dialogClipboard.parent);
    PeerDiscovery *discovery = new PeerDiscovery(45454, peerDialog);

    connect(discovery, &PeerDiscovery::peerFound, [&peerDialog](const QString &ip) {
        const auto peerList = peerDialog->getPeerList();

        if (!peerList->findItems(ip, Qt::MatchExactly).isEmpty()) {
            return;
        }

        peerList->addItem(ip);
    });

    peerDialog->setAttribute(Qt::WA_DeleteOnClose);
    peerDialog->exec();
}
