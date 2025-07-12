#ifndef LIB_MEMORY_HPP
#define LIB_MEMORY_HPP

#include <memory>
#include <utility>
#include "../../Utils/Include/Namespace_Macro.hpp"

using std::make_unique;
using std::unique_ptr;

LIB_MEMORY_NAMESPACE
    template <typename T>
    using PtrUnique = unique_ptr<T>;

    template <typename T, typename... Args>
    auto MakePtr(Args &&...args) {
        return make_unique<T>(std::forward<Args>(args)...);
    }

END_NAMESPACE

#endif // LIB_MEMORY_HPP