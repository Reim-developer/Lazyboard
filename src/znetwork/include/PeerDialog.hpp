#ifndef PEER_DIALOG_HPP
#define PEER_DIALOG_HPP
#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

namespace zclipboard::znetwork {
class PeerDialog : public QDialog {
    Q_OBJECT

   public:
    explicit PeerDialog(QWidget *parent = nullptr);
    QListWidget *getPeerList() const;
    void updateEmptyState();

   private:
    QListWidget *peerList;
    QPushButton *sendButton;
    QLabel *emptyLabel;
    QGridLayout *layout;
    QLabel *infoLabel;

   private:
    static inline constexpr int DIALOG_WIDTH_BASE = 600;
    static inline constexpr int DIALOG_HEIGHT_BASE = 600;
};
}  // namespace zclipboard::znetwork

#endif  // PEER_DIALOG_HPP