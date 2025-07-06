#include "ProcessManager.h"

int ProcessManager(void)
{
    debug("Executed: ProcessManager.c::ProcessManager()", DEBUG, std::cout);

    Interface();
    HostData();
    
    return 0;
}
