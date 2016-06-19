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

#include <hash>
#include "macros.h"

#ifndef RENET_IPV4_ADDRESS_H
#define RENET_IPV4_ADDRESS_H

namespace Renet{
    class IPv4Address{
    enum IPv4Type{
        CLASS_A,
        CLASS_B,
        CLASS_C,
        MULTICAST,
        RESERVED,
        ANY,
        LOOPBACK,
        PRIVATE
    };

    private:
        uint32_t ipAddr;
        uint32_t strToAddr(const char*);

    public:
        static const size_t szAddr = sizeof(uint_32);
        static const uint32_t ipAny = 0x00000000;
        static const uint32_t ipLoopback = 0x7f000001;
        static const uint32_t ipBroadcast = 0xffffffff;
        static const uint32_t ipAllGroup = 0xe0000000;

        explict IPv4Address(uint32_t);
        IPv4Address(const std::string&);
        IPv4Address(const char*);
        IPv4Address(const IPv4Address&);

        operator uint32_t() const;
        operator=(const IPv4Address& _ip);
        operator==(const IPv4Address& _ip);
        operator!=(const IPv4Address& _ip);
        operator<(const IPv4Address& _ip);
        RENET_API friend std::ostream& operator<<(std::ostream& _output, const IPv4Address& _ip);

        bool isAddrType(IPv4Type _type);
        IPv4Type getAddrType();
        getAddrString(char* _outstr);

        static convertAddrString(char* _outstr, const IPv4Address& _ip);
    };
}

namespace std {
 template<> struct hash<Renet::IPv4Address> {
     size_t operator()(const Renet::IPv4Address& _ip) const {
         return std::hash<uint32_t>()(_ip);
     }
};

#endif // RENET_IPV4_ADDRESS_H
