#ifndef ALIAS_TEMPLATE_HPP
#define ALIAS_TEMPLATE_HPP
#include "Namespace_Macro.hpp"
#include <functional>

using std::function;

UTILS_NAMESPACE

    template <typename T>
    using Func = function<T>;
    
END_NAMESPACE

#endif // ALIAS_TEMPLATE_HPP