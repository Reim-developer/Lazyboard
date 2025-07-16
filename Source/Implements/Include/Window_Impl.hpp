#ifndef WINDOW_IMPL_HPP
#define WINDOW_IMPL_HPP
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../../Lib_Memory/Include/Memory.hpp"
#include "../../Utils/Include/Utils.hpp"
#include "../../GUI/Include/Window.hpp"
#include "../../Preload/Include/PreloadPassword.hpp"
#include "../../Core/Include/Enum.hpp"
#include "Theme_Impl.hpp"
#include <QApplication>

using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::AppUtils::Utils;
using ZClipboard::Implements::Theme_Impl;
using ZClipboard::GUI::AppMainWindow;
using ZClipboard::Preload::PreloadPassword;
using ZClipboard::Core::LoginState;
using ZClipboard::AppUtils::LogContext;

IMPLEMENTS_NAMESPACE

    class WindowImplement {
        private:
            using Self = WindowImplement;
            using Window = AppMainWindow;
        
        private:
            PtrUnique<Theme_Impl> themeImpl;
            PtrUnique<AppMainWindow> window;
            PtrUnique<PreloadPassword> preloadPassword;
        
        private:
            bool PreloadPasswordCheck();

        public:
            int LaunchWindow(QApplication *application);

        #if defined(Z_DEBUG)
            private:
                void __LOGGING_ALL_OBJECTS__() {
                    LogContext{}.LogDebug(&themeImpl);
                    LogContext{}.LogDebug(&window);
                    LogContext{}.LogDebug(&preloadPassword);
                }
        #endif

    };

END_NAMESPACE

#endif // WINDOW_IMPL_HPP