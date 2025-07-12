#ifndef GET_BUTTON_HPP
#define GET_BUTTON_HPP
#include <QWidget>
#include <QObject>
#include <QGridLayout>
#include <QPushButton>
#include <QSharedPointer>
#include <QtNetwork/QTcpServer>
#include <QSettings>
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../../Network/Include/NetworkDiscovery.hpp"
#include "../../Language/Include/Translate.hpp"

using ZClipboard::Language::Translate;
using ZClipboard::Network::PeerDiscovery;

GUI_NAMESPACE
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
END_NAMESPACE

#endif  // GET_BUTTON_HPP