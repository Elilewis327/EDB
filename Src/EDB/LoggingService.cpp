#include "EDB.h"

EDB::LoggingService::LoggingService(std::ostream *OutputStream) {
  this->LogOutputStream = OutputStream;
  LoggingService::Log(std::string("Logger session started at ") +
                      std::string(Utility::GetTimestamp()) + std::string("."), SYSINFO);
}

EDB::LoggingService::~LoggingService() {
  LoggingService::Log(std::string("Logger session ended at ") +
                     std::string(Utility::GetTimestamp()) + std::string("."), SYSINFO);
}

EDB::LoggingService::LogTypes EDB::LoggingService::GetLoggingType(std::string LoggingType){
  return LogMap[LoggingType];
}

void EDB::LoggingService::SetLogVerbosity(EDB::LoggingService::LogTypes Level){
  LogVerbosity = Level;
}

void EDB::LoggingService::Log(std::string Message, LogTypes LogLevel) {
  if (LoggingService::LogOutputStream == nullptr) {
    return;
  }

  if (LogLevel <= LogVerbosity) {
    *LoggingService::LogOutputStream << Utility::GetTimestamp() << ": "
                                     << Message << std::endl;
  }
}