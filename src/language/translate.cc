#include "include/translate.hpp"

using zclipboard::language::Translate;

void Translate::translatorWidget(QPushButton* button, LanguageType type, const TransValue& trans) {
    switch (type) {
        case ENGLISH:
            button->setText(trans.LANGUAGE_EN);
            break;

        case VIETNAMESE:
            button->setText(trans.LANGUAGE_VI);
    }
}

void Translate::translatorWidget(QLineEdit* lineEdit, LanguageType type, const TransValue& trans) {
    switch (type) {
        case ENGLISH:
            lineEdit->setPlaceholderText(trans.LANGUAGE_EN);
            break;

        case VIETNAMESE:
            lineEdit->setPlaceholderText(trans.LANGUAGE_VI);
    }
}

void Translate::translatorWidget(QCheckBox* checkBox, LanguageType type, const TransValue& trans) {
    switch (type) {
        case ENGLISH:
            checkBox->setText(trans.LANGUAGE_EN);
            break;

        case VIETNAMESE:
            checkBox->setText(trans.LANGUAGE_VI);
            break;
    }
}

void Translate::translatorWidget(QLabel* label, LanguageType type, const TransValue& trans) {
    switch (type) {
        case ENGLISH:
            label->setText(trans.LANGUAGE_EN);
            break;

        case VIETNAMESE:
            label->setText(trans.LANGUAGE_VI);
            break;
    }
}

void Translate::translatorWidget(QDialog* dialog, LanguageType type, const TransValue& trans) {
    switch (type) {
        case ENGLISH:
            dialog->setWindowTitle(trans.LANGUAGE_EN);
            break;

        case VIETNAMESE:
            dialog->setWindowTitle(trans.LANGUAGE_VI);
            break;
    }
}