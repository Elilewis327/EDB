#include "EDB.h"

std::time_t EDB::Utility::Time = std::time(nullptr);

std::string EDB::Utility::GetTimestamp() {  
  char *Timestamp = new char[50];
  std::strftime(Timestamp, 50, "%FT%T", std::gmtime(&Utility::Time));
  return std::string(Timestamp);
}

json::Document* EDB::Utility::GetJsonDoc(std::string FilePath) {
  std::fstream file;
  file.open(FilePath, std::fstream::in);

  if (!file.good()) {
    throw std::runtime_error("File not found: " + FilePath);
  }

  std::string RawJson = "";

  char c;
  while (file.get(c)) {
    if (!file.eof()) {
      RawJson.push_back(c);
    }
  }

  file.close();

  json::Document *doc = new json::Document();
  doc->Parse(RawJson.c_str());

  if (doc->HasParseError()) {
    std::string ParseError = GetParseError_En(doc->GetParseError());
    std::string ErrorMessage = "\nError occurred while parsing " + FilePath +
                               ". \n Error was: \n\n" + ParseError + "\n\n";
    delete doc;
    throw std::runtime_error(ErrorMessage);
  }

  return doc;
}
