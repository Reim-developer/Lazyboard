#ifndef UTILS_MACRO
#define UTILS_MACRO

#include "../../lib_memory/include/memory.hpp"

using zclipboard::lib_memory::MakePtr;

#define GET_PTR_MACRO(_1, _2, _3, NAME, ...) NAME
#define MAKE_SMART_PTR(...) \
        GET_PTR_MACRO(__VA_ARGS__, MAKE_SMART_PTR_IMPL_2, MAKE_SMART_PTR_IMPL_1)(__VA_ARGS__)

#define ADD_LAYOUT_TO(layout, uiElement, row, column) layout->addWidget(uiElement, row, column)

#define CLASS_BUILD(T, V) template<typename T, typename V>

#define MAKE_SMART_PTR_IMPL_1(T, value) \
        value = MakePtr<T>()

#define MAKE_SMART_PTR_IMPL_2(T, value, ARGS) \
        value = MakePtr<T> ARGS

#define FORWARD(T, value) \
        std::forward<T>(value)

#define VOID_FUNC \
        std::function<void()>

#define LISTENER_NAMESPACE \
        namespace zclipboard::listener { 

#define GUI_NAMESPACE \
        namespace zclipboard::zGui {

#define END_NAMESPACE } 

#endif // UTILS_MACRO