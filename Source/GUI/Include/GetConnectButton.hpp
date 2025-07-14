#ifndef GET_BUTTON_HPP
#define GET_BUTTON_HPP
#include <QWidget>
#include <QObject>
#include <QGridLayout>
#include <QPushButton>
#include <QtNetwork/QTcpServer>
#include <QSettings>
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../../Network/Include/NetworkDiscovery.hpp"
#include "../../Language/Include/Translate.hpp"
#include "../../Core/Include/CoreConnect.hpp"
#include "../../Lib_Memory/Include/Memory.hpp"
#include "../../Listener/Include/ListenerConnect.hpp"

using ZClipboard::Language::Translate;
using ZClipboard::Network::PeerDiscovery;
using ZClipboard::Core::CoreConnect;
using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::Listener::ListenerConnect;
using ZClipboard::Network::NetworkState;

GUI_NAMESPACE
    class GetButton {
        public:
            void SetupConnectButton(QMainWindow *window, QGridLayout *layout);
            void ResetServer();
            QPushButton *GetConnectButton();
            NetworkState *GetNetworkState();

        private:
            CoreConnect BuilderCore;
            ListenerConnect BuilderFn;

        private:
            int type;
            Translate::LanguageType languageType;

        private:
            PtrUnique<QPushButton> getButton;
            PtrUnique<QSettings> settings;
            PtrUnique<PeerDiscovery> peerDiscovery;
            PtrUnique<NetworkState> networkState;

    };
END_NAMESPACE

#endif  // GET_BUTTON_HPP