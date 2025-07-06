#include "Common.h"

void debug(std::string content, bool debug, std::ostream& stream)
{
    if (debug == false)
    {
        return;
    }

    stream << content << std::endl;
}
