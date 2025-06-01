#include "include/corePasswordForm.hpp"

using std::function;
using zclipboard::core::CorePasswordForm;

auto CorePasswordForm::addPasswordFormListener() -> function<void()> {
    const auto function = []() {

    };

    return function;
}