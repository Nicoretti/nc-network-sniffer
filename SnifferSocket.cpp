/**
 * Copyright (C) 2012, Nicola Coretti
 *
 * Author: Nicola Coretti
 * Version: 0.1.0
 * Contact: nico.coretti@googlemail.com
 */
#include "Exception.h"
#include "SnifferSocket.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;



SnifferSocket::SnifferSocket(const char* ifname) {

    // check if interface name is ok
    if (strlen(ifname) > IFNAMSIZ) { 
        throw Exception("Interface name too long!");
    } 
    else {
        this->_ifname = new string(ifname);
    }

    // create socket 
    this->_socket_fd = socket(AF_PACKET, SOCK_DGRAM, 0);
    if (this->_socket_fd == -1) {
        throw Exception(strerror(errno));
    }

    // get interface index
    ifreq request;
    strncpy(request.ifr_name, ifname, IFNAMSIZ);
    if (ioctl(this->_socket_fd, SIOCGIFINDEX, &request) == -1) {
        throw Exception(strerror(errno));
    }
    else {
        this->_interface_index = request.ifr_ifindex;
    }

}

bool SnifferSocket::IsInterfaceInPromiscuousMode() {

    bool in_promiscuous_mode = false;

    ifreq request;
    strncpy(request.ifr_name, this->_ifname->c_str(), IFNAMSIZ);
    // get flags
    if (ioctl(this->_socket_fd, SIOCGIFFLAGS, &request) == -1) {
        throw Exception(strerror(errno));
    }
    else {
        in_promiscuous_mode = ((IFF_PROMISC & request.ifr_flags) != 0) ? true : false;
    }

    return in_promiscuous_mode;
}

void SnifferSocket::TogglePromiscuousMode() {

    ifreq request;
    strncpy(request.ifr_name, this->_ifname->c_str(), IFNAMSIZ);
    request.ifr_flags ^= IFF_PROMISC;
    if (ioctl(this->_socket_fd, SIOCSIFFLAGS, &request) == -1) {
        throw Exception(strerror(errno));
    }
}

void SnifferSocket::EnablePromiscuousMode() {
   
    if (!this->IsInterfaceInPromiscuousMode()) {
        this->TogglePromiscuousMode();
    }
}

void SnifferSocket::DisablePromiscuousMode() {

    if (this->IsInterfaceInPromiscuousMode()) {
        this->TogglePromiscuousMode();
    }
}

SnifferSocket::~SnifferSocket() {

    if (this->_ifname != NULL) { delete this->_ifname; }
}
