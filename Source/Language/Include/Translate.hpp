#ifndef BUTTONS_HPP
#define BUTTONS_HPP
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include <QDialog>
#include "../../Utils/Include/Namespace_Macro.hpp"
#define cstr const char*

LANGUAGE_NAMESPACE

    typedef struct {
        cstr LANGUAGE_EN;
        cstr LANGUAGE_VI;
    } TransValue;

    class Translate {
        public:
            enum LanguageType { ENGLISH, VIETNAMESE };

        public:
            static void translatorWidget(QPushButton* button, LanguageType type, const TransValue& trans);
            static void translatorWidget(QLineEdit* lineEdit, LanguageType type, const TransValue& trans);
            static void translatorWidget(QCheckBox* checkBox, LanguageType type, const TransValue& trans);
            static void translatorWidget(QLabel* label, LanguageType type, const TransValue& trans);
            static void translatorWidget(QDialog* dialog, LanguageType type, const TransValue& trans);
    };

END_NAMESPACE

#endif  // BUTTONS_HPP