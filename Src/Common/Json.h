#pragma once
#include "Common.h"
#include <map>
#include <unordered_set>

class Json
{
    private:
        std::unordered_set<char> tokens = {
            '{','}' ,'[' ,']',',' ,'\"','\'','\n',' ','\t',':',
        };

        void deserialize(std::string json);
        void serialize();

    public:

        Json(std::string json);
        std::string ToString();

        operator std::string() {
            return this->ToString();
        }
};
