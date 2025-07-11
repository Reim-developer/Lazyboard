#ifndef LISTENER_DISCONNECT_HPP
#define LISTENER_DISCONNECT_HPP
#include <QSettings>
#include "../../lib_memory/include/memory.hpp"
#include "../../zGui/include/getButton.hpp"
#include "clearCacheListener.hpp"
#include <QMainWindow>
#define BUILD_CLASS(T, V) template<typename T, typename V>
#define FORWARD(T, value) std::forward<T>(value)
#define VOID_FUNC std::function<void()>

using zclipboard::lib_memory::PtrUnique;
using zclipboard::zGui::GetButton;
using zclipboard::lib_memory::MakePtr;

namespace zclipboard::listener {
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

            BUILD_CLASS(T, V)
            ListenerDisconnect *WithAndThen(T DisconnectImpl::*member, V &&value) {
                Impl.get()->*member = FORWARD(V, value);

                return this;
            }

            ListenerDisconnect *WhenDone() {
                return this;
            }

            VOID_FUNC TryGetListener();
    };
} // namespace zclipboard::listener

#endif // LISTENER_DISCONNECT_HPP