#ifndef PRELOAD_PASSWORD_HPP
#define PRELOAD_PASSWORD_HPP
#include <QObject>
#include <QSettings>
#include <QDialog>
#include <memory>
#include "../../Core/Include/Enum.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"

using std::unique_ptr;
using ZClipboard::Core::HashState;
using ZClipboard::Core::LoginState;

PRELOAD_NAMESPACE

    class PreloadPassword : public QObject {
        Q_OBJECT

    private:
        int setLoginFormGui(const QSettings &settings);

    public slots:
        void onLoginSubmit(HashState hashState);

    private:
        unique_ptr<QDialog> dialog;

    public:
        auto showLoginForm() -> LoginState;
    };

END_NAMESPACE

#endif  // PRELOAD_PASSWORD_HPP