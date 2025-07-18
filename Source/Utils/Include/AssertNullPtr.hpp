#ifndef ASSERT_NULL_PTR_HPP
#define ASSERT_NULL_PTR_HPP

#if !defined (Z_DEBUG)
        #error "Could not include 'AssertNullPtr because 'DEBUG_MODE' is disabled.'"
#endif

#if defined (Z_DEBUG)

    #include <type_traits>
    #include <source_location>
    #include "Logging.hpp"

    using std::is_pointer;
    using std::source_location;
    using ZClipboard::AppUtils::LogContext;

    struct AssertContext {
        const source_location &location = source_location::current();

        /*
        * Detect the null pointer & stderr all information, like:
        *
        * Line number
        *
        * Function
        *
        * File
        *
        * Finally, abort the program.
        *
        * This function is required C++ version 20 or above,
        * and the header `<source_location>` built-in.
        */
        template<typename T>
        void RequireNonNullPtr(T ptr) {
            if(!is_pointer<T>::value) {
                /*
                * Fatal & exit the program now.
                * No-need return or do something.
                */
                LogContext{
                    .location = location
                }.Fatal("Could not check the value: ", ptr, " because it is not a pointer!");
            }

            LogContext{
                .location = location
            }.Fatal("Null-pointer detect, in address: ", ptr);
        }
    };

#endif

#endif // ASSERT_NULL_PTR_HPP