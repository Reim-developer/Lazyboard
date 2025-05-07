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

using zclipboard::zGui::ZDialog;

void ZDialog::showZContentDialog(const QString &text, QTableView *zTableView) {
    QDialog *zContentDialog = new QDialog(zTableView);
    QIcon zIcon = QIcon(":/assets/assets/icon.png");
    QGridLayout *zDialogLayout = new QGridLayout(zContentDialog);

    QPlainTextEdit *zContentArea = new QPlainTextEdit(zContentDialog);
    QPushButton *zCopyButton = new QPushButton(zContentDialog);

    zContentDialog->setWindowTitle("zContent Clipboard");
    zContentDialog->resize(600, 600);
    zContentDialog->setWindowIcon(zIcon);

    zContentArea->setReadOnly(true);
    zContentArea->setPlainText(text);
    zContentArea->setLineWrapMode(QPlainTextEdit::NoWrap);

    zCopyButton->setText("Copy Content");
    zCopyButton->setIcon(QIcon::fromTheme("edit-copy"));

    QPointer<QPushButton> safeCopyButton = zCopyButton;
    connect(zCopyButton, &QPushButton::clicked,
            [safeCopyButton, text, this] { saveTextToClipboard(safeCopyButton, text); });

    zDialogLayout->addWidget(zCopyButton, 1, 0);
    zDialogLayout->addWidget(zContentArea, 0, 0);

    zContentDialog->setAttribute(Qt::WA_DeleteOnClose);
    zContentDialog->exec();
}

void ZDialog::showZImageDialog(const QImage &image, QWidget *parent) {
    QDialog *zDialog = new QDialog(parent);
    QPushButton *saveButton = new QPushButton(zDialog);
    QScrollArea *scrollArea = new QScrollArea(zDialog);
    QGridLayout *zLayout = new QGridLayout(zDialog);
    QLabel *imageLabel = new QLabel(zDialog);

    zDialog->setWindowTitle("zClipboard Image Viewer");
    zDialog->resize(600, 600);

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
