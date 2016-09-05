#ifndef RENET_ETHERNETII_H
#define RENET_ETHERNETII_H

#include "protocol.h"
#include "hw_address.h"

namespace Renet{
    class EthernetII : Protocol{
    private:
        MACAddress destAddr;
        MACAddress srcAddr;

        class EtherType{
        public:
            EtherType(uint16_t _);
        }etherType;
    };

    uint8_t *payload;

    uint32_t chksumCRC;
}

#endif // RENET_ETHERNETII_H
