#include <iostream>
#include <ctime>
#include <fstream>
#include "rapidjson/document.h"
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace json = rapidjson;

class EDB
{
private:
		std::string SchemaDirPath;
		std::ostream* LogOutputStream = nullptr;
		std::time_t time;
		
	public:
		EDB(std::string DefaultConfigFilePath = "Config/config.json", std::ostream* LogStream = &std::cout);
		~EDB();
		void ReadConfig(std::string ConfigFilePath);
		void StartLoggingService(std::ostream* OutputStream);
		void Log(std::string);
		std::string GetTimestamp();
};
