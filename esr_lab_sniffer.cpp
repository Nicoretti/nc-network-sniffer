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
#include "SnifferSocket.h"
// determine user id
#include <unistd.h>
// exit imports
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
    
    SnifferSocket* sniffer_sock = new SnifferSocket("eth0");
    
    cout << "Promiscuous-Mode: " << sniffer_sock->IsInterfaceInPromiscuousMode() << endl;
    sniffer_sock->EnablePromiscuousMode();
    cout << "Promiscuous-Mode: " << sniffer_sock->IsInterfaceInPromiscuousMode() << endl;
    sniffer_sock->DisablePromiscuousMode();
    cout << "Promiscuous-Mode: " << sniffer_sock->IsInterfaceInPromiscuousMode() << endl;
    
    exit(EXIT_SUCCESS);
}
