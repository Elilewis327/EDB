#include "EDB.h"

EDB::EDB(std::string DefaultConfigFilePath, std::ostream *LogStream) {
  try {
    LoggingService::StartLoggingService(LogStream);
    Configuration::ReadConfig(DefaultConfigFilePath);
    // this->ReadSchema();
    // this->StartServer();
    // this->StartInterface();
  } catch (std::runtime_error E) {
    LoggingService::Log(E.what(), LoggingService::ERROR);
  }
  LoggingService::StopLoggingService();
}
