OBJS = Test.o AllOSThread.o ThreadMutex.o

CC = g++

CFLAGS = -Wall -O -g

test:${OBJS}
	${CC} ${OBJS} -o test -lpthread
AllOSThread.o:AllOSThread.cpp AllOSThread.h
	${CC} ${CFLAGS} -c AllOSThread.cpp
ThreadMutex.o:ThreadMutex.cpp ThreadMutex.h
	${CC} ${CFLAGS} -c ThreadMutex.cpp
test.o:Test.cpp AllOSThread.h ThreadMutex.h
	${CC} ${CFLAGS} -c Test.cpp

clean:
	rm -rf *.o test

