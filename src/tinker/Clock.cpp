#include "Clock.h"

Clock::Clock(char** argv)
{
    ticks = atoi(argv[1]);
    rows = atoi(argv[2]);
    cols = atoi(argv[3]);
    routers = new Router*[rows];
    for(int i=0; i<rows; i++)
    {
        routers[i] = new Router[cols];
        for(int j=0; j<cols; j++)
            routers[i][j] = Router(i, j, rows, cols, &routers);
    }
}

int Clock::getTicks(){ return ticks; }

int Clock::tick(int tcnt)
{
    for(int i=0; i<this->rows; i++)
        for(int j=0; j< this->cols; j++)
            this->routers[i][j].tick(tcnt);

    return 1;
}

int main(int argc, char** argv)
{
    if(argc < 4) {
        cout<<"Incorrect syntax.\nCorrect Usage: ./trouting #iterations #rows #cols.\n";
        exit(0);
    }

    Clock clock(argv);
    for(int i=0; i<clock.getTicks();i++) {
        cout<<"\nTick "<<i+1<<":\n";
        clock.tick(i);
        cout<<"\nEnd "<<i+1<<"\n";
    }

    double gen=0.0, sun=0.0, lat=0.0;
    
    for(int i=0;i<clock.rows;i++)
        for(int j=0;j<clock.cols;j++)
        {
            gen+=clock.routers[i][j].getGen();
            sun+=clock.routers[i][j].getSun();
            lat+=clock.routers[i][j].getLatency();
        }

    cout<<"Results:"<<endl;
    cout<<"Number of ports/router: "<<NUM_PORTS<<endl;
    cout<<"Number of buffers/port: "<<NUM_BUFFERS<<endl;
    cout<<"Number of flits/packet: "<<PACKET_SIZE<<endl;
    cout<<"Number of packets/buffer: "<<BUFFER_SIZE<<endl;
    cout<<"Packet generation rate: "<<GEN_PERCENT<<"%"<<endl;
    cout<<endl;
    
    if(gen==0.0) cout<<"Throughput: 0"<<endl<<"Packets Generated: "<<gen<<". Packets Sunk:"<<sun<<endl;
    else cout<<"Throughput: "<<sun*100.0/gen<<endl<<"Packets Generated: "<<gen<<". Packets Sunk:"<<sun<<endl;
    if(sun==0.0) cout<<"Average Latency: 0"<<endl;
    else cout<<"Average Latency: "<<lat/sun<<endl;
    return 0;
}
