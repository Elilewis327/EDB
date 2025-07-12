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
  class Utility {
  public:
    static std::time_t Time;
    static std::string GetTimestamp();
    static json::Document *GetJsonDoc(std::string FilePath);
  };

  class LoggingService {
  public:
    enum LogTypes { SYSINFO = 0, ERROR = 1, WARN = 2, DEBUG = 3, INFO = 4, };
    inline static std::unordered_map<std::string, EDB::LoggingService::LogTypes>
        LogMap = {{"ERROR", EDB::LoggingService::ERROR},
                  {"DEBUG", EDB::LoggingService::DEBUG},
                  {"WARN", EDB::LoggingService::WARN},
									{"INFO", EDB::LoggingService::INFO},
                  {"SYSINFO", EDB::LoggingService::SYSINFO},
									};
    static std::ostream *LogOutputStream;
    static void StartLoggingService(std::ostream *OutputStream);
    static void StopLoggingService();
    static void Log(std::string, LogTypes LogLevel = INFO);
  };

  class Configuration {
  public:
    std::vector<std::string> Schemas;
    static LoggingService::LogTypes LogVerbosity;
    static void ReadConfig(std::string ConfigFilePath);
  };

  EDB(std::string DefaultConfigFilePath = "Config/config.json",
      std::ostream *LogStream = &std::cout);
};
