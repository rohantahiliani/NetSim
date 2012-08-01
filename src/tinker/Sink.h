#include "Common.h"

#ifndef sink_include
#define sink_include

class Sink
{
private:
	int pending;
public:
	Sink();
	void sinkRemove();
	void sinkReceive();
};

#endif
