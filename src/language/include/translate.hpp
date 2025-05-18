#ifndef BUTTONS_HPP
#define BUTTONS_HPP
#include <QPushButton>
#include <QLineEdit>
#include <QAction>

namespace zclipboard::language {

class Translate {
   public:
    enum LanguageType { ENGLISH, VIETNAMESE };

   private:
   public:
    static void translatorWidget(QPushButton* button, LanguageType type, const char* LANGUAGE_EN,
                                 const char* LANGUAGE_VI);
    static void translatorWidget(QLineEdit* lineEdit, LanguageType type, const char* LANGUAGE_EN,
                                 const char* LANGUAGE_VI);
};
}  // namespace zclipboard::language

#endif  // BUTTONS_HPP