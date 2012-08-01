#ifndef common_include
#define common_include

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>
#include <queue>

// Constant Declaration
#define PACKET_SIZE 4

#define MAX_SKIPS 5

#define NUM_BUFFERS 4
#define BUFFER_SIZE 4

#define NUM_PORTS 4

#define INJ_SIZE 16*PACKET_SIZE

#define GEN_PERCENT 50

// Port Directions
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// Packet Stage
#define NOTHING -1 // NULL packet
#define CREATED 0 // Initialized packet
#define PROCESSING 1 // Being routed
#define TRANSFERRING 2 // Transfer to another port
#define TRANSFERRED 3 // Transfer receieved
#define RECEIVED 4 // Received at router
#define SINKING 5 // Sinking at router

using namespace std;

class Packet
{
private:
    int sr, sc, dr, dc;
    int stage;
    int start;
public:
    Packet();
    Packet(int rs, int cs, int rd, int cd, int tick, int s=CREATED);
    void copy(Packet* source);
    int srow();
    int scol();
    int drow();
    int dcol();
    int getStart();
    int getStage();
    void setStage(int s);
};

#endif
