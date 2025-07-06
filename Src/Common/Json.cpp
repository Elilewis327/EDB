#include "Json.h"

Json::Json(std::string json)
{
    this->deserialize(json);
}

std::string Json::ToString()
{
    return "Not Yet";
}

void Json::deserialize(std::string json)
{
    std::string::iterator itr = json.begin();
    bool must_be_symbol = true;

    while(itr != json.end())
    {
        if (must_be_symbol && (this->tokens.find(*itr) != this->tokens.end())){
            if (*itr == '\"' || *itr == '\'')
                must_be_symbol = false;
            else if (*itr == '{'){
            }
        }
        else if (!must_be_symbol){
            if ((*itr == '\"' || *itr == '\'') && *(itr-1) != '\\')
                must_be_symbol = true;

        }
        else {
            std::cerr << "Error parsing JSON string: JSON invalid. Found unexpected symbol " << *itr << " at " << std::distance(json.begin(), itr) << std::endl;
        }


        itr++;
    }
}

void serialize()
{

}
