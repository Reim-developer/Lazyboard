#ifndef CORE_DISCONNECT_HPP
#define CORE_DISCONNECT_HPP
#include <QPushButton>
#include <QObject>
#include "../../Lib_Memory/Include/Memory.hpp"
#include "../../Utils/Include/Meta_Macro.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"

using ZClipboard::Lib_Memory::PtrUnique;
CORE_NAMESPACE

    struct CoreDisconnectImpl {
        QPushButton *disconnectButton;
    };

    class CoreDisconnect {
        private:
            PtrUnique<CoreDisconnectImpl> Impl;

        public:
            CoreDisconnect *StartBuild(QPushButton *button);
            CoreDisconnect *WhenDone();

            void AddListener(VOID_FUNC func);
    };

END_NAMESPACE
#endif // CORE_DISCONNECT_HPP