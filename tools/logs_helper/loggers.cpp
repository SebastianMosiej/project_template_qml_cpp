#include <loggers.h>
#include <QDir>
#include <QFile>
#include <QString>
#include <iostream>
#include <spdlog/sinks/rotating_file_sink.h>
#ifndef NDEBUG
#include <spdlog/sinks/stdout_color_sinks.h>
#endif

bool bLoggersCreated(false);

const QString cLogDir("logs");
const QString cLogsfile= QString("%1%2%3").arg(cLogDir).arg(QDir::separator()).arg("logfile");

void cleanupLogsDir()
{
  // be sure that DIR is created
  QDir().mkdir(cLogDir);
  // cleanup logs dir content
  if (QFile::exists(cLogsfile))
    QFile::remove(cLogsfile);
}

void create_loggers(const std::string& strPluginLogName)
{
  if (bLoggersCreated) {
    spdlog::get("root")->warn("Loggers already created");
    return;
  }

  cleanupLogsDir();
  std::vector<spdlog::sink_ptr> sinks;
#ifndef NDEBUG
  sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
#endif
  sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(cLogsfile.toStdString(), 50*1024*1024, 5));
  auto combined_logger = std::make_shared<spdlog::logger>("root", begin(sinks), end(sinks));
#ifndef NDEBUG
  combined_logger->set_level(spdlog::level::debug);
#else
  combined_logger->set_level(spdlog::level::info);
#endif
  spdlog::register_logger(combined_logger);

  bLoggersCreated = true;

  combined_logger->flush_on(spdlog::level::warn);
  spdlog::flush_every(std::chrono::seconds(5));
}
//////////////////////////////////////////////////////////////////////////
