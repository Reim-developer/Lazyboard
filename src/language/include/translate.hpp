#ifndef BUTTONS_HPP
#define BUTTONS_HPP
#include <QPushButton>

namespace zclipboard::language {
struct TranslateParams {
    QPushButton *button;
    const char *TRANS_VALUE;
};

class Translate {
    static void buttonTrans(const TranslateParams &params);
};
}  // namespace zclipboard::language

#endif  // BUTTONS_HPP