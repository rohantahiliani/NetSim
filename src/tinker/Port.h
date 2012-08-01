#include "Common.h"

#ifndef port_include
#define port_include

class Port
{
private:
    int pid;
    queue<Packet*>** ibuffer;
    queue<Packet*>** obuffer;
public:
    Port(int id);
    int getPid();
    int isFull();
    int putPacket(Packet* packet);
    int getPacket(int bid, Packet** packet);
    int delPacket(int bid, Packet** packet);
};

#endif
