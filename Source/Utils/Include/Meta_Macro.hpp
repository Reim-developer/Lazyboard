#ifndef UTILS_MACRO
#define UTILS_MACRO

#include "../../Lib_Memory/Include/Memory.hpp"

using ZClipboard::Lib_Memory::MakePtr;
using ZClipboard::Lib_Memory::PtrUnique;

#if !defined (_WIN32)
        #define GET_PTR_MACRO(_1, _2, _3, NAME, ...) NAME

        #define MAKE_SMART_PTR(...) \
                GET_PTR_MACRO(__VA_ARGS__, MAKE_SMART_PTR_IMPL_2, MAKE_SMART_PTR_IMPL_1)(__VA_ARGS__)

        #define ADD_LAYOUT_TO(layout, uiElement, row, column) layout->addWidget(uiElement, row, column)

        #define MAKE_SMART_PTR_IMPL_1(T, value) \
                value = MakePtr<T>()

        #define MAKE_SMART_PTR_IMPL_2(T, value, ARGS) \
                value = MakePtr<T> ARGS
#endif

#define CLASS_BUILD(T, V) template<typename T, typename V>

#define FORWARD(T, value) \
        std::forward<T>(value)

#define VOID_FUNC \
        std::function<void()>

#endif // UTILS_MACRO