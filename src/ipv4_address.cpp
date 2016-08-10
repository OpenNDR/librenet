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

#include "../include/macros.h"
#include "../include/ipv4_address.h"

using namespace Renet;

IPv4Address::IPv4Address(uint32_t _ip):ipAddr(_ip){}
IPv4Address::IPv4Address(const std::string& _ip){
    IPv4Address(_ip.c_str());
}
IPv4Address::IPv4Address(const char *_ip){
    (_ip&&_ip!=nullptr) ? strToAddr(_ip, ipAddr) : throw std::runtime_error("Invalid pointer access");
}
IPv4Address::IPv4Address(const IPv4Address& _ip) : ipAddr(_ip.data()){}

std::string IPv4Address::to_string() const{
    return addrToStr(*this);
}
uint32_t IPv4Address::data(){
    return ipAddr;
}

IPv4Address& IPv4Address::operator=(uint32_t _rhs){
    ipAddr = _rhs;
}
IPv4Address& IPv4Address::operator=(const std::string& _rhs){
    *this = _rhs.c_str();
}
IPv4Address& IPv4Address::operator=(const char* _rhs){
    (_rhs&&_rhs!=nullptr) ? strToAddr(_rhs, ipAddr) : throw std::runtime_error("Invalid pointer access");
}
IPv4Address& IPv4Address::operator=(const IPv4Address& _rhs){
    ipAddr = _rhs.data();
}
bool IPv4Address::operator ==(const IPv4Address& _rhs){}
