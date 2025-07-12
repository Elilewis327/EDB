#include "EDB.h"

std::ostream *EDB::LoggingService::LogOutputStream = &std::cout;

void EDB::LoggingService::StartLoggingService(std::ostream *OutputStream) {
  LoggingService::LogOutputStream = OutputStream;
  LoggingService::Log(std::string("Logger session started at ") +
                      std::string(Utility::GetTimestamp()) + std::string("."), SYSINFO);
}

void EDB::LoggingService::StopLoggingService() {
  LoggingService::Log(std::string("Logger session ended at ") +
                      std::string(Utility::GetTimestamp()) + std::string("."), SYSINFO);
  LoggingService::LogOutputStream = nullptr;
}

void EDB::LoggingService::Log(std::string Message, LogTypes LogLevel) {
  if (LoggingService::LogOutputStream == nullptr) {
    return;
  }

  if (LogLevel <= Configuration::LogVerbosity) {
    *LoggingService::LogOutputStream << Utility::GetTimestamp() << ": "
                                     << Message << std::endl;
  }
}