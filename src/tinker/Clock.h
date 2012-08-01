#include "Common.h"
#include "Router.h"

#ifndef clock_include
#define clock_include

void initialize();

class Clock
{
public:
    int ticks;
    int rows;
    int cols;
    Router **routers;
    Clock(char** argv);
    int getTicks();
    int tick(int tcnt);
};

#endif
