#ifndef CORE_PASSWORD_FORM_HPP
#define CORE_PASSWORD_FORM_HPP
#include <QDialog>
#include <QLineEdit>
#include <functional>
#include "Enum.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"

using std::function;
using ZClipboard::Core::HashState;

CORE_NAMESPACE

    class CorePasswordForm {
        public:
            function<HashState()> addPasswordFormListener(QLineEdit *passwordLine, QDialog *parent);
    };

END_NAMESPACE

#endif  // CORE_PASSWORD_FORM_HPP