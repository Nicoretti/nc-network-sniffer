/**
 * Copyright (C) 2012, Nicola Coretti
 *
 * Author: Nicola Coretti
 * Version: 0.1.0
 * Contact: nico.coretti@googlemail.com
 *
 * Time used:
 * 1) create socket, get interface index, set interface to promisc mode
 * about 1 - 1,5h => resources (just manual pages) 
 */

// determine user id
#include <unistd.h>
// socket includes
#include <sys/types.h>
#include <sys/socket.h>
// includes for netdevice
#include <sys/ioctl.h>
#include <net/if.h>

// htons
#include <arpa/inet.h>
// sockaddr_ll import
#include <netpacket/packet.h>
#include <net/ethernet.h>

// perror includes
#include <stdio.h>
#include <errno.h>

#include <stdlib.h>

#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char* argv[], char* envp[]) {

    // check if the user has root prevs
    if (getuid() != 0) {
        cerr << "you have to be root in order to run this program." << endl;
        exit(EXIT_FAILURE);
    }

    int socket_fd;
    // SOCK_DGRAM => Layer 2 header already removed and stored in struct
    // SOCK_RAW => Layer 2 header not removed
    socket_fd = socket(AF_PACKET, SOCK_RAW, 0);
    if (socket_fd == -1) {
        perror("couldn't create socket: "); 
    }

    ifreq request;
    strncpy(request.ifr_name, "lo", IFNAMSIZ);
    if (ioctl(socket_fd, SIOCGIFINDEX, &request) == -1) {
        perror("get index error:");
    }
    cout << "Interface Name: " << request.ifr_name << endl;
    cout << "Interface Index: " << request.ifr_ifindex << endl;
    int index = request.ifr_ifindex;
    // set permiscous mode
    if (ioctl(socket_fd, SIOCGIFFLAGS, &request) == -1) {
        perror("get flags error");
    }
    request.ifr_flags ^= IFF_PROMISC;
    if (ioctl(socket_fd, SIOCSIFFLAGS, &request) == -1) {
        perror("set flags error");
    }

    cout << "user id: " << cuserid(NULL) << endl;

    sockaddr_ll sock;
    sock.sll_family = AF_PACKET;
    sock.sll_protocol = htons(ETH_P_ALL);
    sock.sll_ifindex = index;
    sock.sll_pkttype = PACKET_OTHERHOST;
    if (bind(socket_fd, (sockaddr*) &sock, sizeof(sock)) == -1) {
        cout << strerror(errno) << endl;
        perror("error during bind: ");
    }

    while(true) {
            sockaddr_ll packet_header;
            packet_header.sll_family = AF_PACKET;
            packet_header.sll_protocol = htons(ETH_P_ALL);
            packet_header.sll_ifindex = index;
            packet_header.sll_pkttype = PACKET_OTHERHOST;
            int MTU = 1600;
            uint8_t* buf = new uint8_t[MTU];
            socklen_t sock_size= sizeof(packet_header); 
            ssize_t msg_size = recvfrom(socket_fd, buf, MTU, 0, 
                                       (sockaddr*) &packet_header, &sock_size);

            cout << "msg - length: " << msg_size << endl;

            for (int i = 0; i <= msg_size; i++) {
                cout << " " << buf[i] << " ";
            }
            
            cout << endl << endl;
    }

    exit(EXIT_SUCCESS);
}
