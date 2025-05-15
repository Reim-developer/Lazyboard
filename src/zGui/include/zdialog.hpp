#ifndef ZDIALOG_HPP
#define ZDIALOG_HPP
#include <QDialog>
#include <QString>
#include <QObject>
#include <QTableWidget>
#include <QTableView>
#include <QPushButton>
#include <QImage>
#include <optional>
#include <QPointer>

using std::optional;

namespace zclipboard::zGui {

struct DialogClipboard {
    QPointer<QPushButton> safeButton;
    QDialog *parent;
    const optional<QImage> image;
    const optional<QString> text;
    const optional<QString> clipboardContent;
};

class ZDialog : public QObject {
    Q_OBJECT

   public:
    void showZContentDialog(const QString &text, QTableView *zTableView);
    void showZImageDialog(const QImage &image, QWidget *parent);

   private:
    void saveImage(const DialogClipboard &dialogClipboard);
    void saveTextToClipboard(const DialogClipboard &dialogClipboard);
    void showPeerListDialog(const DialogClipboard &dialogClipboard);

   private:
    inline static constexpr int DIALOG_WIDTH_BASE = 600;
    inline static constexpr int DIALOG_HEIGHT_BASE = 600;
};
}  // namespace zclipboard::zGui

#endif