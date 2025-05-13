#ifndef GET_BUTTON_HPP
#define GET_BUTTON_HPP
#include <QWidget>
#include <QObject>
#include <QGridLayout>
#include <QPushButton>
#include <QtNetwork/QTcpServer>

namespace zclipboard::zGui {
class GetButton : public QObject {
    Q_OBJECT

   public:
    void addGetButton(QWidget *window, QGridLayout *layout);
    void createReceiverServer(QWidget *parent);

   private:
    QPushButton *getButton;
    QTcpServer *server;
};
}  // namespace zclipboard::zGui

#endif  // GET_BUTTON_HPP