/*The MIT License (MIT)
 *
 * Copyright (c) 2016 OpenNDR
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#ifndef __WIN32
    #include <unistd.h>
#else
#endif

#include "macros.h"

#ifndef RENET_MAC_ADDRESS_H
#define RENET_MAC_ADDRESS_H

namespace Renet{
    class MACAddress{
        enum MACType{
            UNICAST,
            MULTICAST,
            BROADCAST
        };

    private:
        uint8_t macAddr[6];
        bool strToAddr(const char* _mac);
        bool addrToStr(char* _outStr);

    public:
        explict MACAddress(uint8_t* _mac);
        MACAddress(const std::string& _mac);
        MACAddress(const char* _mac);
        MACAddress(const MACAddress& _mac);

        static const size_t szAddr = sizeof(uint8_t*6);
        static getBroadcast(uint8_t* _outPtr) const;
        static getBroadcast(MACAddress& _mac) const;

        operator uint8_t*() const;
        operator=(const MACAddress& _mac);
        operator==(const MACAddress& _mac);
        operator!=(const MACAddress& _mac);
        operator<(const MACAddress& _mac);
        RENET_API friend std::ostream& operator<<(std::ostream& _output, const MACAddress& _mac);

        bool isAddrType(MACType _type);
        MACType getAddrType();
        getAddrString(char* _outStr);
    };
}

namespace std {
 template<> struct hash<Renet::MACAddress> {
     size_t operator()(const Renet::MACAddress& _mac) const {
         return std::hash<uint8_t*>()(_mac);
     }
};

#endif // RENET_MAC_ADDRESS_H
