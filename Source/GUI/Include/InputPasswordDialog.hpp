#ifndef GUI_DIALOG_HPP
#define GUI_DIALOG_HPP
#include <QDialog>
#include <QObject>
#include <QLineEdit>
#include <QPushButton>
#include "../../Utils/Include/Namespace_Macro.hpp"

GUI_NAMESPACE
    class InputPasswordDialog : public QObject {
        Q_OBJECT

    private:
        QLineEdit *passwordInputField;
        QLineEdit *passwordInputField2;
        QPushButton *submitButton;
        QPushButton *showPasswordButton;

    private:
        void setupGui(QDialog *parent);

    private:
        static inline const constexpr int DIALOG_WIDTH = 400;
        static inline const constexpr int DIALOG_HEIGHT = 400;

    public:
        void showInputPassword(QDialog *parent);
    };
END_NAMESPACE

#endif  // GUI_DIALOG_HPP
