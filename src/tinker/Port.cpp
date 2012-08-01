#include "Port.h"

Port::Port(int id)
{
    pid = id;
    ibuffer = new queue<Packet*>*[NUM_BUFFERS];
    obuffer = new queue<Packet*>*[NUM_BUFFERS];
    for(int i=0; i<NUM_BUFFERS; i++)
    {
        ibuffer[i]=new queue<Packet*>();
        obuffer[i]=new queue<Packet*>();
    }
}

int Port::getPid() { return pid; }

int Port::isFull(){ 
    for(int i=0; i<NUM_BUFFERS; i++)
        if(ibuffer[i]->size() <= BUFFER_SIZE) { return 0; }
    return 1;
}

int Port::putPacket(Packet* packet)
{
    for(int i=0; i<NUM_BUFFERS; i++)
    {
        if(this->ibuffer[i]->size() < BUFFER_SIZE)
        {
            Packet *p = new Packet();
            p->copy(packet);
            ibuffer[i]->push(p);
            return 1;
        }
    }
    return 0;
}

int Port::getPacket(int bid, Packet** packet)
{
    if(this->ibuffer[bid]->size() > 0)
    {
        *packet = ibuffer[bid]->front();
        return 1;
    }
    *packet=0;
    return 0;
}

int Port::delPacket(int bid, Packet** packet)
{
    if(this->ibuffer[bid]->size() > 0)
    {
        Packet* ptr = ibuffer[bid]->front();
        *packet = new Packet(ptr->srow(), ptr->scol(), ptr->drow(), ptr->dcol(), ptr->getStart(), ptr->getStage());
        ibuffer[bid]->pop();
        return 1;
    }
    *packet=0;
    return 0;
}
