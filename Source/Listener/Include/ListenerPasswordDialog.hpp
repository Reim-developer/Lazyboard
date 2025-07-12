#ifndef LISTENER_DIALOG_HPP
#define LISTENER_DIALOG_HPP
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QSettings>
#include "../../Utils/Include/Namespace_Macro.hpp"

LISTENER_NAMESPACE

    typedef struct {
        QPushButton *showPasswordButton;
        QLineEdit *passwordInputField;
        QLineEdit *passwordInputField2;
        QSettings *settings;
    } ListenerDialogParameters;

    class ListenerDialog : public QObject {
        Q_OBJECT

    public:
        void onChangePassword(const ListenerDialogParameters &params);
        void onSubmitPassword(const ListenerDialogParameters &params, QDialog *parent,
                            QPushButton *submitButton);
    };

END_NAMESPACE

#endif  // LISTENER_DIALOG_HPP