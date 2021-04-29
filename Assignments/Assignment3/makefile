#Benjamin Bishop

CC= g++ -std=c++11

exe: in2post.o stack.o
	$(CC) in2post.o stack.o -o exe

in2post.o: in2post.cpp 
	$(CC) -c in2post.cpp

stack.o: stack.h stack.hpp
	$(CC) -c stack.h
	$(CC) -c stack.hpp	
	
clean:
	rm -rf *o exe
