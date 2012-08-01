# Generated automatically from Makefile.in by configure.
CC=g++
CFLAGS=-g -I/usr/include  -Wall 
LD=-L/usr/lib

all: Common Port Generator Sink Router Clock

LIB = Common.o Generator.o Sink.o Port.o Router.o Clock.o

Common: Common.cpp
	$(CC) $(CFLAGS) Common.cpp -c -o Common.o
Router: Router.cpp
	$(CC) $(CFLAGS) Router.cpp -c -o Router.o
Generator: Generator.cpp
	$(CC) $(CFLAGS) Generator.cpp -c -o Generator.o
Sink: Sink.cpp
	$(CC) $(CFLAGS) Sink.cpp -c -o Sink.o
Port: Port.cpp
	$(CC) $(CFLAGS) Port.cpp -c -o Port.o

Clock:  $(LIB) 
	$(CC) $(CFLAGS) $(LIB) -o trouting

clean:	
	rm *.o trouting
dist:
	rm -rf ${DISTDIR}; mkdir ${DISTDIR}
	cp ${DIST} ${DISTDIR}
	rm -f ${DISTFILE}
	tar cf - ${DISTDIR} | gzip > ${DISTFILE}
