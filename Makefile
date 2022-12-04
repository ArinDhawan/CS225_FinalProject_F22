CC = g++
CFLAGS = -g -w -Wall

main: main.o 
	$(CC) $(CFLAGS) -o main main.o 

main.o: entry/main.cpp
	$(CC) $(CFLAGS) -c entry/main.cpp

clean:
	rm -f core *.o main



