#include "include/translate.hpp"

using zclipboard::language::Translate;

void Translate::translatorWidget(QPushButton* button, LanguageType type, const char* LANGUAGE_EN,
                                 const char* LANGUAGE_VI) {
    switch (type) {
        case ENGLISH:
            button->setText(LANGUAGE_EN);
            break;

        case VIETNAMESE:
            button->setText(LANGUAGE_VI);
    }
}

void Translate::translatorWidget(QLineEdit* lineEdit, LanguageType type, const char* LANGUAGE_EN,
                                 const char* LANGUAGE_VI) {
    switch (type) {
        case ENGLISH:
            lineEdit->setPlaceholderText(LANGUAGE_EN);
            break;

        case VIETNAMESE:
            lineEdit->setPlaceholderText(LANGUAGE_VI);
    }
}