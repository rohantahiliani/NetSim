#include "Common.h"

#ifndef generator_include
#define generator_include

class Generator
{
private:
	int rows, cols;
public:
	Generator();
	Generator(int r, int c);
	int getRandom(int max);
	int generate(int sr, int sc, int* dr, int* dc);
};

#endif
