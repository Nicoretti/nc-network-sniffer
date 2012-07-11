CXX_FLAGS = -ggdb -Wall -Werror 

all: sniffer esr_test

esr_test: esr_test.cpp
	$(CXX) $(CXX_FLAGS) -o test esr_test.cpp
	
sniffer: esr_lab_sniffer exception sniffer_socket
	$(CXX) $(CXX_FLAGS) -o sniffer esr_lab_sniffer.o exception.o sniffer_socket.o

esr_lab_sniffer: exception
	$(CXX) $(CXX_FLAGS) -o esr_lab_sniffer.o -c esr_lab_sniffer.cpp 

exception: Exception.h Exception.cpp
	$(CXX) $(CXX_FLAGS) -o exception.o -c Exception.cpp

sniffer_socket: SnifferSocket.h SnifferSocket.cpp
	$(CXX) $(CXX_FLAGS) -o sniffer_socket.o -c SnifferSocket.cpp
	
clean:
	rm -f *.o
	rm -f sniffer
	rm -f test
