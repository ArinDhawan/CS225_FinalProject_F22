CC = g++
CFLAGS = -g -w -Wall

main: main.o 
	$(CC) $(CFLAGS) -o main main.o 

main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp

clean:
	rm -f core *.o main
