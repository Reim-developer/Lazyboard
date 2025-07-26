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

            /*
            * Ascii terminal color list.
            */
            struct Ascii_Color {
                static inline const constexpr char RED[] = "\e[0;31m";
                static inline const constexpr char GREEN[] = "\e[0;32m";
                static inline const constexpr char WHITE[] = "\e[0;37m";
                static inline const constexpr char YELLOW[] = "\e[0;33m";
            };

            /*
            * Only for debug mode is enabled.
            */
            struct LogContext {
                /*
                * If you wish wrapper, use the field `location` in this struct.
                * Otherwise, it's optional.
                */
                const std::source_location &location = std::source_location::current();

                /*
                * Logging for debug & stdout all pointer address.
                * Required C++ 20 or above.
                */
                template<typename... Args>
                inline void LogDebug(Args&&... args) noexcept {
                    DEBUG << Ascii_Color::GREEN << "[DEBUG_MODE] In File: " 
                                  << Ascii_Color::YELLOW << location.file_name() << "\n";

                    DEBUG << Ascii_Color::GREEN << "[DEBUG_MODE] In Function: " 
                                  << Ascii_Color::YELLOW << location.function_name() << "\n";

                    DEBUG << Ascii_Color::GREEN << "[DEBUG_MODE] In Line: " 
                                  << Ascii_Color::YELLOW << location.line() << "\n";

                    DEBUG << Ascii_Color::GREEN << "[DEBUG_MODE] Address: ";

                    (DEBUG << ... << (DEBUG << Ascii_Color::YELLOW, args));
                    DEBUG << Ascii_Color::WHITE; /* Reset to white, default of terminal. */
                    DEBUG << "\n";
              
                }

                /*
                * Logging for case critical error
                * & quit the program now.
                * Required for C++ 20 or above.
                */
                template<typename... Args>
                inline void Fatal(Args&&... args) noexcept {
                    ERROR << Ascii_Color::RED << "[CRITICAL] In Function: "
                                 << Ascii_Color::GREEN << location.function_name() << "\n";

                    ERROR << Ascii_Color::RED << "[CRITICAL] In Line: "
                                 << Ascii_Color::GREEN << location.line() << "\n";

                    ERROR << Ascii_Color::RED << "[CRITICAL] In File: "
                                 << Ascii_Color::GREEN << location.file_name() << "\n";
                    
                    ERROR << Ascii_Color::RED << "[CRITICAL] ";
                    (ERROR << ... << (ERROR << Ascii_Color::YELLOW, args));
                    ERROR << "\n";
                    ERROR << Ascii_Color::WHITE; /* Reset to white, default of terminal. */

                    std::abort();
                }
            };

        END_NAMESPACE
    #endif
#endif // LOGGING_HPP