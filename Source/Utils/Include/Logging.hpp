#ifndef LOGGING_HPP
#define LOGGING_HPP
    #if !defined (Z_DEBUG)
        #error "Cannot include 'Logging' because debug mode is disabled."
    #endif

    #if defined(Z_DEBUG)
        #define MIN_CPP_VERSION 20200L
        #if __cplusplus < MIN_CPP_VERSION
            #error "Cannot use the feature 'Logging because current C++ version is lower than 20.'"
        #endif

        #include "Namespace_Macro.hpp"
        #include <source_location>
        #include <cstdlib>
        #include <iostream>
    
        using std::cout;
        using std::cerr;

        #define DEBUG cout
        #define ERROR cerr

        /* This macro is only working if you already
        *  defined the logging function '__LOGGING_ALL_OBJECTS()'
        *  in your header file.
        *  For security reason, please use it 
        *  in debugging mode only.
        */
        #define __LOG__ __LOGGING_ALL_OBJECTS__();
        

        UTILS_NAMESPACE
            static inline const constexpr char RED[] = "\e[0;31m";
            static inline const constexpr char GREEN[] = "\e[0;32m";
            static inline const constexpr char WHITE[] = "\e[0;37m";
            static inline const constexpr char YELLOW[] = "\e[0;33m";

            /*
            * Only for debug mode is enabled.
            */
            struct LogContext {
                const std::source_location &location = std::source_location::current();

                /*
                * Logging for debug & stdout all pointer address.
                * Required C++ 20 or above.
                */
                template<typename... Args>
                void LogDebug(Args&&... args) {
                    DEBUG << " [DEBUG_MODE] In File:" 
                                << location.file_name()<< "\n";

                    DEBUG << "[DEBUG_MODE] In Function:" 
                                << location.function_name() << "\n";

                    DEBUG << "[DEBUG_MODE] In Line:" 
                                << location.line() << "\n";

                    DEBUG << "[DEBUG_MODE] Address:";

                    (DEBUG << ... << args);
                    DEBUG << "\n";
                }

                /*
                * Logging for case critical error
                * & quit the program now.
                * Required for C++ 20 or above.
                */
                template<typename... Args>
                void Fatal(Args&&... args) {
                    ERROR << RED << "[CRITICAL] In Function: "
                                 << GREEN << location.function_name() << "\n";

                    ERROR << RED << "[CRITICAL] In Line: "
                                 << GREEN << location.line() << "\n";

                    ERROR << RED << "[CRITICAL] In File: "
                                 << GREEN << location.file_name() << "\n";
                    
                    ERROR << RED << "[CRITICAL] ";
                    (ERROR << ... << (ERROR << YELLOW, args));
                    ERROR << "\n";
                    ERROR << WHITE; /* Reset to white, default of terminal. */
                    std::abort();
                }
            };

        END_NAMESPACE
    #endif
#endif // LOGGING_HPP