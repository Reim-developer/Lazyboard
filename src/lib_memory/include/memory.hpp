#ifndef Z_LIB_MEMORY
#define Z_LIB_MEMORY

#include <memory>
#include <utility>

using std::make_unique;
using std::unique_ptr;

namespace zclipboard::lib_memory {
    template <typename T>
    using PtrUnique = unique_ptr<T>;

    template <typename T, typename... Args>
    auto MakePtr(Args &&...args) {
        return make_unique<T>(std::forward<Args>(args)...);
    }
}  // namespace zclipboard::lib_memory

#endif