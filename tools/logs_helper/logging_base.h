#ifndef LOG_HELPER_LOGGING_BASE_H
#define LOG_HELPER_LOGGING_BASE_H
#include <QtCore/QString>
#include <memory>
#include <loggers.h>
#include <spdlog/spdlog.h>

namespace logger_helper {

    class LoggingBase {
    public:
        LoggingBase(std::string category = "root");
        ~LoggingBase();
        void logConnection(const QString &strClassName, const QString &strConnDesc, bool bResult);
        void log(eLogLevel debugLevel, const char *msg);
        void log(eLogLevel debugLevel, const std::string &msg);
        void log(eLogLevel debugLevel, QString msg);

    public:
        std::shared_ptr<spdlog::logger> logger;
    private:
    };
}

#endif //LOG_HELPER_LOGGING_BASE_H
