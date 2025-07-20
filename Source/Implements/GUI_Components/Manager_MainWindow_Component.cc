#include "Include/Manager_MainWindow_Component_Impl.hpp"

using ZClipboard::Implements::MainWindowComponentsManager;

using Self = MainWindowComponentsManager;
using Window = QMainWindow;

Self *Self::StartBuild() {
    if(!Impl) {
        Utils::MakeSmartPtr<DataImpl>(Impl);
    }

    return this;
}

Object *Self::GetObject() {
    return this
        ->  Impl
        ->  object;
}

QIcon *Self::GetAppIcon() {
    return this
        ->  Impl
        ->  appIcon;
}

Window *Self::GetWindow() {
    return this
        ->  Impl
        ->  window;
}

Toolkit *Self::GetToolkit() {
    return this
        ->  Impl
        ->  toolkit;
}

Self *Self::WhenDone() {
    return this;
}

void Self::Render_MainWindow_GUI() {
    auto object = this->GetObject();
    auto toolkit = this->GetToolkit();
    auto appIcon = this->GetAppIcon();
    auto window = this->GetWindow();

    TableViewComponentImpl(object, toolkit);
    ClearButtonComponentImpl(object, toolkit);
    SearchAreaComponentImpl(object, toolkit);
    NotificationComponentImpl(object, toolkit);
    SystemTrayComponentImpl(window, object, toolkit, *appIcon);
    ConnectButtonComponentImpl(window, object, toolkit);
    DisconnectButtonComponentImpl(window, object, toolkit);
    SettingButtonComponentImpl(window, object, toolkit);
}