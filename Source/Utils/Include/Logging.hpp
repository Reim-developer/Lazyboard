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
        #include <QDebug>

        /* This macro is only working if you already
        *  defined the logging function '__LOGGING_ALL_OBJECTS()'
        *  in your header file.
        *  For security reason, please use it 
        *  in debugging mode only.
        */
        #define __LOG__ __LOGGING_ALL_OBJECTS__();
        

        UTILS_NAMESPACE

            /*
            * Only for debug mode is enabled.
            */
            struct LogContext {
                const std::source_location &location = std::source_location::current();

                template<typename... Args>
                void LogDebug(Args&&... args) {
                    auto debugStream = qDebug().noquote();

                    debugStream << " [DEBUG_MODE] In File:" 
                                << location.file_name()<< "\n";

                    debugStream << "[DEBUG_MODE] In Function:" 
                                << location.function_name() << "\n";

                    debugStream << "[DEBUG_MODE] In Line:" 
                                << location.line() << "\n";

                    debugStream << "[DEBUG_MODE] Address:";

                    (debugStream << ... << args);
                    debugStream << "\n";
                }
            };

        END_NAMESPACE
    #endif
#endif // LOGGING_HPP