#include "Common.h"

Packet::Packet()
{
    this->setStage(NOTHING);
}

Packet::Packet(int rs, int cs, int rd, int cd, int tick, int s)
{
    sr = rs;
    sc = cs;
    dr = rd;
    dc = cd;
    start = tick;
    this->setStage(s);
}

void Packet::copy(Packet* source)
{
    this->sr = source->sr;
    this->sc = source->sc;
    this->dr = source->dr;
    this->dc = source->dc;
    this->start = source->start;
    this->stage = source->stage;
}

int Packet::srow() { return this->sr; }

int Packet::scol() { return this->sc; }

int Packet::drow() { return this->dr; }

int Packet::dcol() { return this->dc; }

int Packet::getStart() { return this->start; }

int Packet::getStage() { return this->stage; }

void Packet::setStage(int s) { this->stage = s; }
