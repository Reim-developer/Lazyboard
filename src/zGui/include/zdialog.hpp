#ifndef ZDIALOG_HPP
#define ZDIALOG_HPP
#include <QDialog>
#include <QString>
#include <QObject>
#include <QTableWidget>
#include <QTableView>
#include <QPushButton>
#include <QImage>

namespace zclipboard::zGui {
class ZDialog : public QObject {
    Q_OBJECT

   public:
    void showZContentDialog(const QString &text, QTableView *zTableView);
    void showZImageDialog(const QImage &image, QWidget *parent);

   private:
    void saveImage(QPointer<QPushButton> safeButton, QDialog *parent, const QImage &image);
    void saveTextToClipboard(QPointer<QPushButton> safeButton, const QString &text);
};
}  // namespace zclipboard::zGui

#endif