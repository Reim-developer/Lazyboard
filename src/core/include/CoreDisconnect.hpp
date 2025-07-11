#ifndef CORE_DISCONNECT_HPP
#define CORE_DISCONNECT_HPP
#include <QPushButton>
#include <QObject>
#include "../../lib_memory/include/memory.hpp"
#define BUILD_CLASS(T, V) template<typename T, typename V>
#define VOID_FUNC std::function<void()>

using zclipboard::lib_memory::PtrUnique;

namespace zclipboard::core {
    struct CoreDisconnectImpl {
        QPushButton *disconnectButton;
    };

    class CoreDisconnect {
        private:
            PtrUnique<CoreDisconnectImpl> coreDisconnectImpl;

        public:
            CoreDisconnect *StartBuild(QPushButton *button);
            CoreDisconnect *WhenDone();

            void AddListener(VOID_FUNC func);
    };
} // namespace zcliboard::core

#endif // CORE_DISCONNECT_HPP