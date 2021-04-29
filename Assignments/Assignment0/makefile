#Benjamin Bishop
#main.cpp
#stack.h

CC= g++ -std=c++11

exe: main.o  
	$(CC) main.o -o exe

main.o: main.cpp stack.h 
	$(CC) -c main.cpp 
	$(CC) -c stack.h

clean:
	rm -rf *o exe
