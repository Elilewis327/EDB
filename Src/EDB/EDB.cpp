#include "EDB.h"
#include "rapidjson/document.h"

EDB::EDB(std::string DefaultConfigFilePath, std::ostream *LogStream) {
  this->Logger = new LoggingService(LogStream);
  try {
    ReadConfig(DefaultConfigFilePath);
    // this->ReadSchema();
    // this->StartServer();
    // this->StartInterface();
  } catch (std::runtime_error E) {
    Logger->Log(E.what(), LoggingService::ERROR);
  }

  delete Logger;
}

void EDB::ReadConfig(std::string ConfigFilePath) {
  json::Document *config = Utility::GetJsonDoc(ConfigFilePath);

  { // MaxLogLevel
    json::Value::MemberIterator itr = config->FindMember("MaxLogLevel");
    if (itr == config->MemberEnd()) {
      LogConfigFile(config, LoggingService::ERROR);
      throw std::runtime_error(
          "Invalid Configuration, No 'MaxLogLevel' attr found.");
    }

    std::string level = itr->value.GetString();
    Logger->SetLogVerbosity(Logger->GetLoggingType(level));

    LogConfigFile(config, LoggingService::INFO);

    Logger->Log(std::format("Set log level to {}", level),
                LoggingService::INFO);
  }

  { // Schemas
    json::Value::MemberIterator itr = config->FindMember("Schemas");

    if (itr == config->MemberEnd()) {
      LogConfigFile(config, LoggingService::ERROR);
      throw std::runtime_error(
          "Invalid Configuration, No 'Schemas' attr found.");
    }

    if (!itr->value.IsObject()) {
      LogConfigFile(config, LoggingService::ERROR);
      throw std::runtime_error(
          "Invalid Configuration, 'Schemas' attr found expected to be type "
          "'Object' with at least one member named 'default'.");
    }

    for (json::Value::ConstMemberIterator s = itr->value.MemberBegin();
         s != itr->value.MemberEnd(); ++s) {
					std::string schema_name = s->name.GetString();
					std::string schema_value = s->value.GetString();
					this->Schemas[schema_name] = schema_value;
							
				Logger->Log(std::format("Added Schema {}:{}", schema_name, schema_value),
                LoggingService::INFO);
    }

  }

  delete config;
}

void EDB::LogConfigFile(json::Document *config,
                        LoggingService::LogTypes level) {
  json::StringBuffer buffer;
  json::Writer<json::StringBuffer> writer(buffer);
  config->Accept(writer);
  Logger->Log(buffer.GetString(), level);
}