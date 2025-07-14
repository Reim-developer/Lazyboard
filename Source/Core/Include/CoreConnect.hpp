#ifndef CORE_CONNECT_BUTTON
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../../Utils/Include/Meta_Macro.hpp"
#include "../../Lib_Memory/Include/Memory.hpp"
#include <QPushButton>
#include <QSettings>

using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::Lib_Memory::MakePtr;

CORE_NAMESPACE
    struct CoreConnectImpl {
        QPushButton *button;
    };

    class CoreConnect {
        private:
            PtrUnique<CoreConnectImpl> Impl;

        public:
            CoreConnect *StartBuild() {
                #if !defined(_WIN32)

                    MAKE_SMART_PTR(CoreConnectImpl, Impl);
                    return this;

                #else

                    Impl = MakePtr<CoreConnectImpl>();
                    return this;

                #endif 
            }
            
            private:
                using Implement = CoreConnectImpl;

            public:
                CLASS_BUILD(T, V)
                CoreConnect *WithAndThen(T Implement::*member, V &&value) {
                    Impl.get()->*member = FORWARD(V, value);

                    return this;
                }

                CoreConnect *WhenDone() {
                    return this;
                }

                void ThenAddListener(VOID_FUNC function);
    };

END_NAMESPACE

#endif // CORE_CONNECT_BUTTON