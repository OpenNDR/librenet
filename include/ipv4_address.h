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

//System Headers
#ifndef __WIN32
    #include <unistd.h>
#else
#endif

//Custom Headers
#include "macros.h"
#include "ipv4_address.h"

//Cxx Standard Headers
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <sstream>
#include <iterator>

#ifndef RENET_IPV4_ADDRESS_H
#define RENET_IPV4_ADDRESS_H

namespace Renet{
    class IPv4Address{
    public:
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

        static const IPv4Address ipAny;
        static const IPv4Address ipLoopback;
        static const IPv4Address ipBroadcast;
        static const IPv4Address ipAllGroup;

        explicit IPv4Address(uint32_t _ip);
        explicit IPv4Address(const std::string& _ip);
        explicit IPv4Address(const char* _ip);
        IPv4Address(const IPv4Address& _ip);

        std::string to_string() const;
        uint32_t data() const;

        IPv4Address& operator=(uint32_t _rhs);
        IPv4Address& operator=(const std::string& _rhs);
        IPv4Address& operator=(const char* _rhs);
        IPv4Address& operator=(const IPv4Address& _rhs);

        bool operator==(const std::string& _rhs) const;
        bool operator==(const char* _rhs) const;
        bool operator==(const IPv4Address& _rhs) const;

        bool operator!=(const std::string& _rhs) const;
        bool operator!=(const IPv4Address& _rhs) const;

        bool operator<(const std::string& _rhs) const;
        bool operator<(const char* _rhs) const;
        bool operator<(const IPv4Address& _rhs) const;

        bool operator>(const std::string& _rhs) const;
        bool operator>(const char* _rhs) const;
        bool operator>(const IPv4Address& _rhs) const;

        bool operator<=(const std::string& _rhs) const;
        bool operator<=(const char* _rhs) const;
        bool operator<=(const IPv4Address& _rhs) const;

        bool operator>=(const std::string& _rhs) const;
        bool operator>=(const char* _rhs) const;
        bool operator>=(const IPv4Address& _rhs) const;

        IPv4Address operator&(const std::string& _rhs) const;
        IPv4Address operator&(const char* _rhs) const;
        IPv4Address operator&(const IPv4Address& _rhs) const;

        IPv4Address& operator&=(const std::string& _rhs);
        IPv4Address& operator&=(const char* _rhs);
        IPv4Address& operator&=(const IPv4Address& _rhs);
        RENET_API friend std::ostream& operator<<(std::ostream& _output, const IPv4Address& _ip);

        IPv4Type getAddrType() const;
        bool isAddrType(IPv4Type _type) const;

    private:
        uint32_t ipAddr;
        static const size_t szAddr = sizeof(uint32_t);

        inline void strToAddr(std::string _hw, uint32_t _addr);
        static std::string addrToStr(const IPv4Address& _hw);
    };

    const IPv4Address IPv4Address::ipAny = IPv4Address(0x00000000);
    const IPv4Address IPv4Address::ipLoopback = IPv4Address(0x7f000001);
    const IPv4Address IPv4Address::ipBroadcast = IPv4Address(0xffffffff);
    const IPv4Address IPv4Address::ipAllGroup = IPv4Address(0xe0000000);

}//Namespace Renet

namespace std {
 template<> struct hash<Renet::IPv4Address> {
     size_t operator()(const Renet::IPv4Address& _ip) const {
         return std::hash<std::string>()(_ip.to_string());
     }
};

#endif // RENET_IPV4_ADDRESS_H
