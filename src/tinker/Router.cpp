#include "Router.h"

Router::Router() {
}

Router::Router(int r, int c, int rows, int cols, Router*** ters) {
    rid = r;
    cid = c;
    routers = *ters;
    available = INJ_SIZE;
    generator = Generator(rows, cols);
    sink = Sink();
    gen=0; sun=0; latency=0;
    ports = new Port*[NUM_PORTS];
    for(int i=0;i<NUM_PORTS;i++)
        ports[i] = new Port(i);
}

int Router::getAvailable() {
    return this->available;
}

int Router::getDirection(Packet* packet) {
    if (packet->dcol() != this->cid) //Traverse X
    {
        if (packet->dcol() < this->cid) return WEST;
        else if (packet->dcol() > this->cid) return EAST;
    }
    else if (packet->drow() != this->rid) //Traverse Y
    {
        if (packet->drow() < this->rid) return SOUTH;
        else if (packet->drow() > this->rid) return NORTH;
    }
    return -1;
}

int Router::route(Packet* packet) {
    int direction;
    if ((direction = getDirection(packet)) >= 0)
    {
        cout<<"Routing packet towards "<<direction<<" at "<<this->rid<<" "<<this->cid<<" to "<<packet->drow()<<" "<<packet->dcol()<<endl;
        if(direction == WEST) {
            if(routers[this->rid][this->cid-1].ports[direction]->isFull()) return 0;
            routers[this->rid][this->cid-1].receive(EAST, packet);
        }
        else if(direction == EAST) {
            if(routers[this->rid][this->cid+1].ports[direction]->isFull()) return 0;
            routers[this->rid][this->cid+1].receive(WEST, packet);
        }
        else if(direction == NORTH) {
            if(routers[this->rid+1][this->cid].ports[direction]->isFull()) return 0;
            routers[this->rid+1][this->cid].receive(SOUTH, packet);
        }
        if(direction == SOUTH) {
            if(routers[this->rid-1][this->cid].ports[direction]->isFull()) return 0;
            routers[this->rid-1][this->cid].receive(NORTH, packet);
        }
    }
    else
    {
        cout << "Invalid route\n";
        return 1;
    }
    return 1;
}

void Router::receive(int port, Packet* packet) {
    cout<<"Received at: "<<this->rid << " " << this->cid << " on Port: "<<ports[port]->getPid()<<endl;
    packet->setStage(RECEIVED);
    ports[port]->putPacket(packet);
}

void Router::injest() {
    Packet* packet = 0;
    if (inject.size() == 0) return;
    packet = inject.front();
    int direction = getDirection(packet);
    cout<<"Router: "<<this->rid <<" "<<this->cid<<" Injesting at port:"<<ports[direction]->getPid()<<endl;
    if(ports[direction]->isFull()) return;
    packet->setStage(PROCESSING);
    ports[direction]->putPacket(packet);
    inject.pop();
    available += PACKET_SIZE;
}

void Router::transfer(int bid, int sport, int dport) {
    Packet* packet = 0;
    ports[sport]->delPacket(bid, &packet);
    packet->setStage(TRANSFERRED);
    if(ports[dport]->putPacket(packet))
        cout<<"Packet transferred from "<<sport<<" to "<<dport<<" at "<<this->rid<<" "<<this->cid<<endl;
    else
        cout<<"Packet dropped going from "<<sport<<" to "<<dport<<" at "<<this->rid<<" "<<this->cid<<endl;
    delete packet;
}

void Router::tick(int tcnt) {
    int dr=0, dc=0;
    if (available>PACKET_SIZE && this->generator.generate(this->rid, this->cid, &dr, &dc)) {
        cout << "Packet generated to go From: " << this->rid << " " << this->cid << " To: " << dr << " " << dc << endl;
        Packet *packet = new Packet(this->rid, this->cid, dr, dc, tcnt);
        packet->setStage(CREATED);
        this->inject.push(packet);
        available -= PACKET_SIZE;
        gen++;
    }
    for (int i = 0; i < NUM_PORTS; i++)
    {
        for(int j=0; j< NUM_BUFFERS; j++)
        {
            Packet* packet = 0;
            ports[i]->getPacket(j, &packet);
            if(packet == 0) continue;
            switch(packet->getStage())
            {
                case PROCESSING:
                    if(this->route(packet))
                    {
                        this->ports[i]->delPacket(j, &packet);
                        delete packet;
                    }
                    break;
                case TRANSFERRING:
                    this->transfer(j, i, this->getDirection(packet));
                    break;
                case RECEIVED:
                    if(this->getDirection(packet)<0) {
                        packet->setStage(SINKING);
                    }
                    else packet->setStage(TRANSFERRING);
                    break;
                case TRANSFERRED:
                    packet->setStage(PROCESSING);
                    break;
                case SINKING:
                    cout << "Sinking packet from: " << this->rid << " " << this->cid << endl;
                    this->sink.sinkReceive();
                    this->ports[i]->delPacket(j, &packet);
                    sun++;
                    latency+=(tcnt-packet->getStart()+PACKET_SIZE);
                    delete packet;
                    break;
                default:
                    ports[i]->delPacket(j, &packet);
                    delete packet;
                    break;
            }
        }
    }
    this->injest();
    this->sink.sinkRemove();
}

int Router::getGen() { return gen; }
int Router::getSun() { return sun; }
int Router::getLatency() { return latency; }