#ifndef ZDIALOG_HPP
#define ZDIALOG_HPP
#include <QDialog>
#include <QString>
#include <QObject>
#include <QTableWidget>
#include <QTableView>
#include <QPushButton>
#include <QImage>
#include <QtNetwork/QTcpServer>
#include <QPointer>

namespace zclipboard::zGui {
class ZDialog : public QObject {
    Q_OBJECT

   public:
    void showZContentDialog(const QString &text, QTableView *zTableView);
    void showZImageDialog(const QImage &image, QWidget *parent);

   private:
    void saveImage(QPointer<QPushButton> safeButton, QDialog *parent, const QImage &image);
    void saveTextToClipboard(QPointer<QPushButton> safeButton, const QString &text);
    void showPeerListDialog(QDialog *parent);
    void createReceiverServer(QDialog *parent);
    void showReceiverDialog(QDialog *parent);

   private:
    inline static constexpr int DIALOG_WIDTH_BASE = 600;
    inline static constexpr int DIALOG_HEIGHT_BASE = 600;
};
}  // namespace zclipboard::zGui

#endif