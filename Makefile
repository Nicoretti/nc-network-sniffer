CXX_FLAGS = -ggdb -Wall -Werror 

all: sniffer

sniffer: esr_lab_sniffer exception sniffer_socket
	$(CXX) $(CXX_FLAGS) -o sniffer esr_lab_sniffer.o exception.o message.o sniffer_socket.o pretty_printer.o

esr_lab_sniffer: exception sniffer_socket pretty_printer
	$(CXX) $(CXX_FLAGS) -o esr_lab_sniffer.o -c esr_lab_sniffer.cpp 

exception: Exception.h Exception.cpp
	$(CXX) $(CXX_FLAGS) -o exception.o -c Exception.cpp

sniffer_socket: SnifferSocket.h SnifferSocket.cpp message
	$(CXX) $(CXX_FLAGS) -o sniffer_socket.o -c SnifferSocket.cpp

pretty_printer: PrettyPrinter.h PrettyPrinter.cpp message
	$(CXX) $(CXX_FLAGS) -o pretty_printer.o -c PrettyPrinter.cpp

message: Message.h Message.cpp
	$(CXX) $(CXX_FLAGS) -o message.o -c Message.cpp


	
clean:
	rm -f *.o
	rm -f sniffer
	rm -f test
