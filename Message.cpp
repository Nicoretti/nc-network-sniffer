/**
 * Copyright (C) 2012, Nicola Coretti
 *
 * Author: Nicola Coretti
 * Version: 0.1.0
 * Contact: nico.coretti@googlemail.com
 */

#include "Message.h"
#include <string.h>

const char* Message::GetProtocolName(PROTOCOL protocol) {

    const char* protocol_name = NULL;
    switch (protocol) {

        case Message::IPv4:
            protocol_name = "IPv4";
            break;

        case Message::IPv6:
            protocol_name = "IPv6";
            break;

        case Message::ICMP:
            protocol_name = "ICMP";
            break;

        case Message::ICMPv6:
            protocol_name = "ICMPv6";
            break;

        case Message::TCP:
            protocol_name = "TCP";
            break;

        case Message::UDP:
            protocol_name = "UDP";
            break;

        default:
            protocol_name = "Unknown";
            break;
    }

    return protocol_name;
}

Message::PROTOCOL Message::ExtractLayer3Protocol(uint8_t* data_buffer) {

    Message::PROTOCOL l3_protocol = Message::UNKNOWN;
    uint16_t type = ((uint16_t) (data_buffer[12] << 8)) | ((uint16_t) data_buffer[13]);
    switch (type) {

        case 0x0800:
            l3_protocol = Message::IPv4;
            break;

        case 0x86DD:
            l3_protocol = Message::IPv6;
            break;

        default:
            l3_protocol = Message::UNKNOWN;
            break;
    }

    return l3_protocol;
}


Message::PROTOCOL Message::ExtractLayer4Protocol(uint8_t* data_buffer, Message::PROTOCOL layer3_protocol) {

    Message::PROTOCOL l4_protocol = Message::UNKNOWN;
    uint8_t type = 0x00;
    // select field which indicates the next higher protocol type
    if (layer3_protocol == Message::IPv4) {

        type = data_buffer[23];
    }
    else if (layer3_protocol == Message::IPv6) {

        type = data_buffer[30];
    }

    // determine protocol
    switch (type) {

        case 0x01:
            l4_protocol = Message::ICMP;
            break;

        case 0x06:
            l4_protocol = Message::TCP;
            break;

        case 0x11:
            l4_protocol = Message::UDP;
            break;

        case 0x3a:
            l4_protocol = Message::ICMPv6;
            break;

        default:
            l4_protocol = Message::UNKNOWN;
            break;
    }

    return l4_protocol;
}

Message::Message(uint8_t* data_buffer, uint32_t buffer_length, uint32_t data_length) {

    this->_data_buffer = data_buffer;
    this->_data_buffer_length = buffer_length;
    this->_data_length = data_length;
    this->_layer3_protocol = this->ExtractLayer3Protocol(data_buffer);
    this->_layer4_protocol = this->ExtractLayer4Protocol(data_buffer, this->_layer3_protocol);
    this->_src_address = new uint8_t[6];
    this->_dst_address = new uint8_t[6];
    (void) memcpy(this->_dst_address, data_buffer, 6);
    (void) memcpy(this->_src_address, data_buffer + 6, 6);
}

uint8_t* Message::GetDataBuffer() {

    return this->_data_buffer;
}

uint32_t Message::GetDataBufferLength() {

    return this->_data_buffer_length;
}

uint32_t Message::GetDataLength() {

    return this->_data_length;
}

uint8_t* Message::GetPayload() {

    return this->_payload;
}

uint32_t Message::GetPayloadLength() {

    return this->_payload_length;
}

uint8_t* Message::GetSourceAddress() {

    return this->_src_address;
}

uint8_t* Message::GetDestinationAddress() {

    return this->_dst_address;
}

Message::PROTOCOL Message::GetLayer3Protocol() {

    return this->_layer3_protocol;
}

Message::PROTOCOL Message::GetLayer4Protocol() {

    return this->_layer4_protocol;
}

Message::~Message() {

    if (this->_data_buffer != NULL) { delete this->_data_buffer; }
    if (this->_src_address != NULL) { delete this->_src_address; }
    if (this->_dst_address != NULL) { delete this->_dst_address; }
}
