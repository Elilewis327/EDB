#include "EDB.h"
#include "rapidjson/document.h"

EDB::EDB(std::string DefaultConfigFilePath, std::ostream *LogStream) {
  this->time = std::time(nullptr);
  this->StartLoggingService(LogStream);
  this->ReadConfig(DefaultConfigFilePath);
  // this->ReadSchema();
  // this->StartServer();
  // this->StartInterface();
}

EDB::~EDB(){
	this->Log(std::string("Logger session ended at ") +
            std::string(this->GetTimestamp()) + std::string("."));
	this->LogOutputStream = nullptr;
}

std::string EDB::GetTimestamp() {
  char *Timestamp = new char[50];
  std::strftime(Timestamp, 50, "%FT%T", std::gmtime(&this->time));
  return std::string(Timestamp);
}

void EDB::StartLoggingService(std::ostream *OutputStream) {
  this->LogOutputStream = OutputStream;
  this->Log(std::string("Logger session started at ") +
            std::string(this->GetTimestamp()) + std::string("."));
}

void EDB::Log(std::string Message) {
  if (this->LogOutputStream != nullptr) {
    *this->LogOutputStream << this->GetTimestamp() << ": " << Message
                           << std::endl;
  }
}

void EDB::ReadConfig(std::string ConfigFilePath) {
  std::fstream file;
  file.open(ConfigFilePath, std::fstream::in);
	
	if (!file.good()){
		throw std::runtime_error("File not found: " + ConfigFilePath); 
	}

	char* buff = new char[65000];

	int i = 0;
	char c;
	while (file.get(c) && i < 65000) {
			buff[i++] = c;
	}

	this->Log(std::string(buff, i));

	delete[] buff;

	json::Document doc;
	json::Value v;
	v.SetString("Hi",doc.GetAllocator());
	doc.AddMember("v", v, doc.GetAllocator());
	json::StringBuffer buffer;
	json::Writer<json::StringBuffer> writer(buffer);
	doc.Accept(writer);

	std::string jsonStr = buffer.GetString();
	std::cout << jsonStr << std::endl;

  file.close();
}
