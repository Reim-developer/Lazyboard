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
#include "../Toolkit/Include/MainWindow_Components.hpp"

using ZClipboard::Language::Translate;
using ZClipboard::Network::PeerDiscovery;
using ZClipboard::Core::CoreConnect;
using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::Listener::ListenerConnect;
using ZClipboard::Network::NetworkState;
using ZClipboard::GUI::Toolkit::ComponentsToolkit;

GUI_NAMESPACE
    class ConnectButton {
        private:
            using Toolkit = ComponentsToolkit;
            using FnConnect = ListenerConnect;
            using LanguageType = Translate::LanguageType;
            using Window = QMainWindow;
            using Button = QPushButton;

        public:
            void SetupConnectButton(Window *window, Toolkit *toolkit);
            void ResetServer();
            NetworkState *GetNetworkState();

        private:
            void SetupEventListener(Window *window, Button *connectButton);

        private:
            CoreConnect BuilderCore;
            ListenerConnect BuilderFn;

        private:
            int type;
            LanguageType languageType;

        private:
            PtrUnique<QSettings> settings;
            PtrUnique<PeerDiscovery> peerDiscovery;
            PtrUnique<NetworkState> networkState;

    };
END_NAMESPACE

#endif  // GET_BUTTON_HPP