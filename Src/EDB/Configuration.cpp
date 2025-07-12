#include "EDB.h"

EDB::LoggingService::LogTypes EDB::Configuration::LogVerbosity = EDB::LoggingService::WARN;

void EDB::Configuration::ReadConfig(std::string ConfigFilePath) {
  json::Document* config = Utility::GetJsonDoc(ConfigFilePath);

  json::StringBuffer buffer;
  json::Writer<json::StringBuffer> writer(buffer);
  config->Accept(writer);

  LoggingService::Log(buffer.GetString(), LoggingService::INFO);
  
	json::Value::MemberIterator itr = config->FindMember("MaxLogLevel");
  if (itr != config->MemberEnd()){
    std::string key = itr->value.GetString();
    Configuration::LogVerbosity = LoggingService::LogMap[key];
    LoggingService::Log(std::format("Set log level to {}", key), LoggingService::INFO);
  }

  delete config;
}
