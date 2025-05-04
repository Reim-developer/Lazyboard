#include "include/zdialog.hpp"
#include <QPointer>
#include <QGridLayout>
#include <QPushButton>
#include <QIcon>
#include <QPlainTextEdit>
#include <QApplication>
#include <QClipboard>
#include <QTimer>

using zclipboard::zGui::ZDialog;

void ZDialog::showZContentDialog(const QString &text, QTableView *zTableView) {
    QDialog *zContentDialog = new QDialog(zTableView);
    QIcon zIcon = QIcon(":/assets/assets/icon.png");
    QGridLayout *zDialogLayout = new QGridLayout(zContentDialog);

    QPlainTextEdit *zContentArea = new QPlainTextEdit();
    QPushButton *zCopyButton = new QPushButton();

    zContentDialog->setWindowTitle("zContent Clipboard");
    zContentDialog->resize(600, 600);
    zContentDialog->setWindowIcon(zIcon);

    zContentArea->setReadOnly(true);
    zContentArea->setPlainText(text);
    zContentArea->setLineWrapMode(QPlainTextEdit::NoWrap);

    zCopyButton->setText("Copy Content");
    zCopyButton->setIcon(QIcon::fromTheme("edit-copy"));

    QPointer<QPushButton> zSafeCopyButton = zCopyButton;
    
    connect(zCopyButton, &QPushButton::clicked, [zSafeCopyButton, text] {
        QApplication::clipboard()->setText(text);
        
        if(zSafeCopyButton) {
            zSafeCopyButton->setText("Copied!");

            QTimer::singleShot(1500, [zSafeCopyButton]() {
                if (zSafeCopyButton) zSafeCopyButton->setText("Copy Content");
            });
        }
    });

    zDialogLayout->addWidget(zCopyButton, 1, 0);
    zDialogLayout->addWidget(zContentArea, 0, 0);

    zContentDialog->setAttribute(Qt::WA_DeleteOnClose);
    zContentDialog->exec();
}
