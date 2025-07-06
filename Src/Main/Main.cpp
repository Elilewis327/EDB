#include "Main.h"

int main(int argc, char * argv[])
{
    debug("Executed: Main.c::Main()", DEBUG, std::cout);

    Json parsed_json("{\"hello\":\"This is Json\"}");
    debug(parsed_json, DEBUG, std::cout);
    
    ReadSchema();
    ProcessManager();

    return 0;
}
