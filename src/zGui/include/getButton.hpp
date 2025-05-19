#ifndef GET_BUTTON_HPP
#define GET_BUTTON_HPP
#include <QWidget>
#include <QObject>
#include <QGridLayout>
#include <QPushButton>
#include <QSharedPointer>
#include <QtNetwork/QTcpServer>
#include <QSettings>
#include "../../znetwork/include/PeerDiscovery.hpp"
#include "../../language/include/translate.hpp"

using zclipboard::language::Translate;
using zclipboard::znetwork::PeerDiscovery;

namespace zclipboard::zGui {
class GetButton : public QObject {
    Q_OBJECT

   public:
    void addGetButton(QWidget *window, QGridLayout *layout);
    void createReceiverServer(QWidget *window);
    void resetServer();
    QPushButton *getConnectButton() const;
    QTcpServer *getServer();

   private:
    int type;
    Translate::LanguageType languageType;

   private:
    QPushButton *getButton;
    QSettings *settings;
    QTcpServer *server = nullptr;
    PeerDiscovery *peer;
};
}  // namespace zclipboard::zGui

#endif  // GET_BUTTON_HPP