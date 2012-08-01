#include "Common.h"
#include "Port.h"
#include "Generator.h"
#include "Sink.h"

#ifndef router_include
#define router_include

class Router
{
private:
    int rid, cid;
    int available; //inj queue 
    Port** ports;
    Sink sink;
    Generator generator;
    Router** routers;
    queue<Packet*> inject;
    int gen, sun, latency;

public:
    Router();
    Router(int r, int c, int rows, int cols, Router*** ters);
    int getAvailable();
    int route(Packet* packet);
    void receive(int port, Packet* packet);
    void transfer(int bid, int sport, int dport);
    int getDirection(Packet* packet);
    void injest();
    void tick(int tcnt);
    int getGen();
    int getSun();
    int getLatency();
};

#endif
