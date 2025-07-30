#include <cstddef>
#include <ctime>
#include <format>
#include <fstream>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace json = rapidjson;

class EDB {
public:

	//Utility
	//All methods need to be atomic.
	//All methods need to be deterministic
  class Utility {
  public:
    static std::string GetTimestamp();
    static json::Document *GetJsonDoc(std::string FilePath);
  };

  class LoggingService {
  public:
    enum LogTypes {
      SYSINFO = 0,
      ERROR = 1,
      WARN = 2,
      DEBUG = 3,
      INFO = 4,
    };

    LoggingService(std::ostream *OutputStream);
    LoggingService();
		~LoggingService();
    void Log(std::string, LogTypes LogLevel = INFO);
		LogTypes GetLoggingType(std::string LogLevel);
		void SetLogVerbosity(LogTypes Level);

		private:
		  std::ostream *LogOutputStream;
			LoggingService::LogTypes LogVerbosity = LoggingService::INFO;
				
			std::unordered_map<std::string, EDB::LoggingService::LogTypes> LogMap = {
				{"SYSINFO", EDB::LoggingService::SYSINFO},
				{"ERROR", EDB::LoggingService::ERROR},
				{"DEBUG", EDB::LoggingService::DEBUG},
				{"WARN", EDB::LoggingService::WARN},
				{"INFO", EDB::LoggingService::INFO},
    	};
  };

  EDB(std::string DefaultConfigFilePath = "Config/config.json",
      std::ostream *LogStream = &std::cout);

	private:
		LoggingService* Logger = nullptr;
	  std::unordered_map<std::string, std::string> Schemas = {};
  	void ReadConfig(std::string ConfigFilePath);
		void LogConfigFile(json::Document* config, LoggingService::LogTypes level = EDB::LoggingService::LogTypes::INFO);

};
