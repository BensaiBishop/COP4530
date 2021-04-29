#Benjamin Bishop
#test_list.cpp
#List.h
#List.hpp

CC= g++ -std=c++11

exe: test_list.o  
	$(CC) test_list.o -o exe

test_list.o: test_list.cpp List.h List.hpp 
	$(CC) -c test_list.cpp 
	$(CC) -c List.h
	$(CC) -c List.hpp

clean:
	rm -rf *o exe
