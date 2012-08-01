#include "Generator.h"

Generator::Generator()
{
}

Generator::Generator(int r, int c)
{
    rows = r;
    cols = c;
    srand(time(0));
}

int Generator::getRandom(int max)
{
    int r = rand()%max;
    return r;
}

int Generator::generate(int sr, int sc, int* dr, int* dc)
{
    int skipped = 0;
    if(this->getRandom(100) > GEN_PERCENT) goto skip; //Skip packet generation 40% of the time

rerand:
    *dr=this->getRandom(this->rows);
    *dc=this->getRandom(this->cols);
    if(sr==*dr && sc==*dc)
    {
        skipped++;
        if(skipped < MAX_SKIPS)	goto rerand;
        else goto skip;
    }

    return 1; //Packet generated from (sr,sc) to (dr,dc)

skip:
    return 0; // Rerandomized 5 times
}
