#ifndef LOGGING_HPP
#define LOGGING_HPP
    #if defined(Z_DEBUG)
        #include "Namespace_Macro.hpp"
        #include <source_location>
        #include <QDebug>

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