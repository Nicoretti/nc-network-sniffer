/**
 * Copyright (C) 2012, Nicola Coretti
 *
 * Author: Nicola Coretti
 * Version: 0.1.0
 * Contact: nico.coretti@googlemail.com
 */

#ifndef SNIFFER_SOCKET_H
#define SNIFFER_SOCKET_H

// socket includes
#include <sys/types.h>
#include <sys/socket.h>

// netdevice includes
#include <sys/ioctl.h>
#include <net/if.h>

// perror includes
#include <stdio.h>
#include <errno.h>

#include <string>

/**
 * A Sniffer socket can be used to network traffic on a
 * network interface. 
 */
class SnifferSocket {

private:

    int _socket_fd;

    int _interface_index;

    std::string* _ifname;


    void TogglePromiscuousMode();

public:


    /**
     * Creates a new SnifferSocket for the specified interface.
     *
     * @param ifname: name of the network interface which will 
     *                be used for sniffing.
     */
    SnifferSocket(const char* ifname);

    /**
     * Checks whether the interface this SnifferSocket is attached
     * to is in promiscuous mode or not.
     *
     * @return <code>true</code> if the interface is in promiscuous
     *          mode, otherwise <code>false</code>.
     */
    bool IsInterfaceInPromiscuousMode();

    /**
     * Enables the promiscuous mode of the interface this SnifferSocket
     * is attached to.
     */
    void EnablePromiscuousMode();

    /**
     * Disables the promiscuous mode of the interface this 
     * SnifferSocket is attached to.
     */
    void DisablePromiscuousMode();


    /**
     * Cleans up the mess.
     */
    ~SnifferSocket();
}; 

#endif /* SNIFFER_SOCKET_H */
