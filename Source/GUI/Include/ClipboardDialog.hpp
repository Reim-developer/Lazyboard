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
#include "../../Utils/Include/Namespace_Macro.hpp"

using std::optional;

GUI_NAMESPACE

    struct ClipboardProperty {
        QPointer<QPushButton> safeButton;
        QDialog *parent;
        const optional<QImage> image;
        const optional<QString> text;
        const optional<QString> clipboardContent;
    };

    class ClipboardDialog : public QObject {
        Q_OBJECT

    public:
        void showZContentDialog(const QString &text, QTableView *zTableView);
        void showZImageDialog(const QImage &image, QWidget *parent);

    private:
        void saveImage(const ClipboardProperty &property);
        void saveTextToClipboard(const ClipboardProperty &property);
        void showPeerListDialog(const ClipboardProperty &property);

    private:
        inline static constexpr int DIALOG_WIDTH_BASE = 600;
        inline static constexpr int DIALOG_HEIGHT_BASE = 600;
    };

END_NAMESPACE

#endif