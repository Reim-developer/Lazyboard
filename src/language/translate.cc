#include "include/translate.hpp"

using zclipboard::language::Translate;
using zclipboard::language::TranslateParams;

void Translate::buttonTrans(const TranslateParams &params) {
    params.button->setText(params.TRANS_VALUE);
}