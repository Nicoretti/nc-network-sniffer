/**
 * Copyright (C) 2012, Nicola Coretti
 *
 * Author: Nicola Coretti
 * Version: 0.1.0
 * Contact: nico.coretti@googlemail.com
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdint.h>

// TODO: Comment
/**
 * This class provides an abstraction for a raw message recieved from an
 * raw socket. It provides detailed information about:
 *  -
 *  - 
 *  - 
 *  and also makes the payload of the package available.
 */
class Message {

public:

    enum PROTOCOL { IPv4, IPv6, ICMP, ICMPv6, TCP, UDP,  UNKNOWN };

private:

    uint8_t* _data_buffer;

    uint32_t _data_buffer_length;

    uint32_t _data_length;

    uint8_t* _payload;

    uint32_t _payload_length;

    uint8_t* _src_address;

    uint8_t* _dst_address;

    PROTOCOL _layer3_protocol;

    PROTOCOL _layer4_protocol;
   
    /**
     * Extracts the layer 3 protocol type form the ethernet frame.
     */
    PROTOCOL ExtractLayer3Protocol(uint8_t* data_buffer);

    /**
     * Extracts the layer 4 protocol type form the ethernet frame.
     *
     * ICMP - will be handled as layer4 protocol, but it isn't
     * a true layer 4 protocol.
     */
    PROTOCOL ExtractLayer4Protocol(uint8_t* data_buffer, PROTOCOL layer3_protocol);

public: 

    /**
     * Creates a new Message based on the supplied buffer and it's data.
     *
     * @param raw_data_buffer: which contains the whole message data.
     * ATTENTION: The Message will take ownership of the buffer,
     *            therefore it will delete the buffer when the Message
     *            is deleted.
     * @param buffer_length: length of the supplied buffer.
     * @param data_length: amount of data in the buffer.
     *                     (buffer_length - data_length = free space in buffer)
     */
    Message(uint8_t* raw_data_buffer, uint32_t buffer_length, uint32_t data_length);

    /**
     * Returns the buffer which contains the raw data.
     */
    uint8_t* GetDataBuffer();

    /**
     * Returns the length of the raw data buffer.
     */
    uint32_t GetDataBufferLength();

    /**
     * Returns the length of the data in the buffer.
     */
    uint32_t GetDataLength();

    /**
     * Returns the buffer which contains the payload.
     */
    uint8_t* GetPayload();

    /**
     * Returns the length of the payload.
     */
    uint32_t GetPayloadLength();

    /**
     * Gets the source address. layer 2 address.
     */
    uint8_t* GetSourceAddress();

    /**
     * Gets the destination address. layer 2 address.
     */
    uint8_t* GetDestinationAddress(); 

    /**
     * Gets the included layer 3 protocol of this message.
     */
    PROTOCOL GetLayer3Protocol();

    /**
     * Gets the included layer 4 protocol of this message.
     */
    PROTOCOL GetLayer4Protocol();

    /**
     * Gets the name as c string for a specified protocol.
     *
     * @param protocol: whose name will be determined.
     *
     * @return the name of the specified protocol, if 
     * it can't determined the string "Unkown" is returned.
     */
    const char* GetProtocolName(PROTOCOL protocol);
    
    /**
     * Cleans up the mess.
     */
    ~Message(); 

};

#endif /* MESSAGE_H */
