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
    const char* ifname = "lo";
    SnifferSocket* sniffer_sock = new SnifferSocket(ifname);
    while (true) {
    
        Message* msg = sniffer_sock->ReceiveMessage();

        cout << "Message-Length: " << dec << msg->GetDataLength();
        cout << "Type: " << msg->GetLayer3Protocol() << " ";
        cout << msg->GetProtocolName(msg->GetLayer3Protocol());
        cout << " Layer-4: " << msg->GetProtocolName(msg->GetLayer4Protocol()) << endl;
        for (uint32_t i = 0; i < msg->GetDataLength(); i++) {
            cout << hex << (int) msg->GetDataBuffer()[i];
        }
        cout << endl << endl;
        delete msg;
    }
    exit(EXIT_SUCCESS);
}
