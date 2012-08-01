#include "Sink.h"

Sink::Sink()
{
    pending = 0;
}

void Sink::sinkRemove()
{
    if(this->pending > 0)
    {
        this->pending--;
        cout<<"Ejected flit from sink.\n";
    }
}

void Sink::sinkReceive()
{
    this->pending+=PACKET_SIZE;
    cout<<"Packet added to sink for removal.\n";
}

