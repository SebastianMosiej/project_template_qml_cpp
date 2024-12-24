#include "logging_base.h"
#include <qglobal.h>
#include <spdlog/logger.h>

namespace logger_helper {
    LoggingBase::LoggingBase(std::string category) : logger(spdlog::get(category)) {
      if (!logger) {
        std::vector<spdlog::sink_ptr> sinks = spdlog::get("root")->sinks();
        auto combined_logger = std::make_shared<spdlog::logger>(category, begin(sinks), end(sinks));
        spdlog::register_logger(combined_logger);
        combined_logger->flush_on(spdlog::level::warn);
        logger = combined_logger;
        logger->flush_on(spdlog::level::warn);
      }
    }
    LoggingBase::~LoggingBase() {}

    void LoggingBase::logConnection(const QString &strClassName, const QString &strConnDesc, bool bResult) {
      QString strDebug = QString("%1: Connection %2").arg(strClassName).arg(strConnDesc);

      if (bResult) {
        strDebug += " SUCCESS";
        log(eDebugLogLevel, strDebug);
      } else {
        strDebug += " --FAIL--";
        log(eWarningLogLevel, strDebug);
      }

      Q_ASSERT_X(bResult, strClassName.toStdString().c_str(), strDebug.toStdString().c_str());
    }

    void LoggingBase::log(eLogLevel debugLevel, QString msg) {
      log(debugLevel, msg.toStdString());
    }

    void LoggingBase::log(eLogLevel debugLevel, const std::string &msg) {
      switch(debugLevel) {
        case eDebugLogLevel:
          logger->debug(msg);
          break;
        case eInfoLogLevel:
          logger->info(msg);
          break;
        case eWarningLogLevel:
          logger->warn(msg);
          break;
        case eErrorLogLevel:
          logger->error(msg);
          break;
        default:
          break;
      }
    }

    void LoggingBase::log(eLogLevel debugLevel, const char *msg) {
      switch(debugLevel) {
        case eDebugLogLevel:
          logger->debug(msg);
          break;
        case eInfoLogLevel:
          logger->info(msg);
          break;
        case eWarningLogLevel:
          logger->warn(msg);
          break;
        case eErrorLogLevel:
          logger->error(msg);
          break;
        default:
          break;
      }

    }
}
