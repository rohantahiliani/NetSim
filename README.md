NetSim
======

A network simulator that performs XY routing


/* Compiling */
make

/* Clean */
make clean

/** Running **/

/* Syntax */
./trouting #iterations #rows #cols

/* Stats */
./trouting #iterations #rows #cols|tail

/** Example **/

/* Command */


./trouting 10000 4 4|tail

/* Output */
Results:
Number of ports/router: 4
Number of buffers/port: 4
Number of flits/packet: 4
Number of packets/buffer: 4
Packet generation rate: 50%

Throughput: 99.7235
Packets Generated: 81722. Packets Sunk:81496
Average Latency: 29.998

/** Description **/
The program creates a network simulation that will run the simulator with N iterations on an RxC node network.

It will display the basic configuration and stats for the run.

The three command-line parameters can be changed at any time.

The other parameters that are displayed in the first part of the results need to be changed before compiling and running. These parameters can be set to anything desired by the user, and they can be used to test different kinds of networks. Each time these parameters are changed, the program should be cleaned, compiled and run.

/** Feedback **/
If you require more control or some new parameters to simulate production networks, please drop a comment or post an email and I will try and get that feature out.