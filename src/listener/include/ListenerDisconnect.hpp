#ifndef LISTENER_DISCONNECT_HPP
#define LISTENER_DISCONNECT_HPP
#include <QSettings>
#include "../../lib_memory/include/memory.hpp"
#include "../../zGui/include/getButton.hpp"
#include "clearCacheListener.hpp"
#include <QMainWindow>
#include "../../zUtils/include/macro.hpp"

using zclipboard::lib_memory::PtrUnique;
using zclipboard::zGui::GetButton;
using zclipboard::lib_memory::MakePtr;

LISTENER_NAMESPACE
    struct DisconnectImpl {
        QSettings *setting;
        GetButton *getButton;
        QMainWindow *windowParent;
    };

    class ListenerDisconnect {
        private:
            PtrUnique<DisconnectImpl> Impl;

        public:
            ListenerDisconnect *StartBuild() {
                Impl = MakePtr<DisconnectImpl>();

                return this;
            }

            CLASS_BUILD(T, V)
            ListenerDisconnect *WithAndThen(T DisconnectImpl::*member, V &&value) {
                Impl.get()->*member = FORWARD(V, value);

                return this;
            }

            ListenerDisconnect *WhenDone() {
                return this;
            }

            VOID_FUNC TryGetListener();
    };
END_NAMESPACE

#endif // LISTENER_DISCONNECT_HPP