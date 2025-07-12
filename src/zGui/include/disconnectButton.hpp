#ifndef DISCONNECT_BUTTON_HPP
#define DISCONNECT_BUTTON_HPP
#include <QPushButton>
#include <QGridLayout>
#include <QMainWindow>
#include "../../lib_memory/include/memory.hpp"
#include "getButton.hpp"
#include "../../core/include/CoreDisconnect.hpp"
#include "../../listener/include/ListenerDisconnect.hpp"
#include "../../zUtils/include/macro.hpp"

using zclipboard::zGui::GetButton;
using zclipboard::lib_memory::PtrUnique;
using zclipboard::core::CoreDisconnect;
using zclipboard::listener::ListenerDisconnect;

GUI_NAMESPACE
    class DisconnectButton {
        private:
            PtrUnique<QSettings> settings;
            CoreDisconnect Builder;
            ListenerDisconnect BuilderFunc;
            PtrUnique<QPushButton> disconnectButton;

        public:
            void addDisconnectButton(QMainWindow *parent, GetButton *getButton, QGridLayout *layout);
            QPushButton *getDisconnectButton();
        };
END_NAMESPACE

#endif  // DISCONNECT_BUTTON_HPP