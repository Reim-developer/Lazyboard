#include "Include/Launch_App_Impl.hpp"
#include "Include/Window_Impl.hpp"
using ZClipboard::Implements::WindowImplement;

int Lauch_App(int argc, char **argv) {
    PtrUnique<QApplication> application = MakePtr<QApplication>(argc, argv);
    PtrUnique<WindowImplement> windowImpl = MakePtr<WindowImplement>();

    return windowImpl->LaunchWindow(application.get());
}