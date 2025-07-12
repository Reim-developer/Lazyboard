#ifndef PASSWORD_FORM_LISTENER_HPP
#define PASSWORD_FORM_LISTENER_HPP
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <functional>
#include "../../Core/Include/Enum.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"

using std::function;
using ZClipboard::Core::HashState;

LISTENER_NAMESPACE

    class PasswordFormListener : public QObject {
        Q_OBJECT

    public:
        void onSubmitPassword(QPushButton *submitButton, QLineEdit *passwordLine, QDialog *parent,
                            function<HashState()> lambda);

    signals:
        void loginResult(HashState hashState);
    };

END_NAMESPACE

#endif  // PASSWORD_FORM_LISTENER_HPP