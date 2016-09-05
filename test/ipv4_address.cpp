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

IPv4Address::IPv4Address(typeData _ip):ipAddr(_ip){}
IPv4Address::IPv4Address(const std::string& _ip){
    IPv4Address(_ip.c_str());
}
IPv4Address::IPv4Address(const char *_ip){
    (_ip&&_ip!=nullptr) ? strToAddr(_ip, ipAddr) : throw std::runtime_error("Invalid pointer access");
}
IPv4Address::IPv4Address(const IPv4Address& _ip) : ipAddr(_ip.data()){}

iterator IPv4Address::begin(){
    return reinterpret_cast<uint8_t>(&ipAddr);
}
const_iterator IPv4Address::begin(){
    return reinterpret_cast<uint8_t>(&ipAddr);
}
iterator IPv4Address::end(){
    return reinterpret_cast<uint8_t>(&ipAddr) + 4;
}
const_iterator IPv4Address::end(){
    return reinterpret_cast<uint8_t>(&ipAddr) + 4;
}

size_t IPv4Address::len() const{
    return 4;x
}
size_t IPv4Address::size() const{
    return 4;
}
std::string IPv4Address::to_string() const{
    return addrToStr(*this);
}
typeData IPv4Address::data() const{
    return ipAddr;
}

typeData& IPv4Address::data(){
    return ipAddr;
}

IPv4Address& IPv4Address::operator=(typeData _rhs){
    ipAddr = _rhs;
    return *this;
}
IPv4Address& IPv4Address::operator=(const std::string& _rhs){
    *this = _rhs.c_str();
    return *this;
}
IPv4Address& IPv4Address::operator=(const char* _rhs){
    (_rhs&&_rhs!=nullptr) ? strToAddr(_rhs, ipAddr) : throw std::runtime_error("Invalid pointer access");
    return *this;
}
IPv4Address& IPv4Address::operator=(const IPv4Address& _rhs){
    ipAddr = _rhs.data();
    return *this;
}

uint8_t operator[](size_t i) const{
    return begin()[i];
}

uint8_t& operator[](size_t i){
    return begin()[i];
}

bool IPv4Address::operator==(const std::string& _rhs) const{
    return ipAddr == _rhs.c_str();
}

bool IPv4Address::operator==(const char* _rhs) const{
    typeData tmpData;
    strToAddr(_rhs, tmpData);
    return ipAddr == tmpData;
}

bool IPv4Address::operator==(const IPv4Address& _rhs) const{
    return ipAddr == _rhs.data();
}

bool IPv4Address::operator!=(const std::string& _rhs) const{
    return !(*this == _rhs);
}

bool IPv4Address::operator!=(const IPv4Address& _rhs) const{
    return !(*this == _rhs);
}

bool IPv4Address::operator<(const std::string& _rhs) const{
    return *this < _rhs.c_str();
}

bool IPv4Address::operator<(const char* _rhs) const{
     typeData tmpData;
     strToAddr(_rhs, tmpData);
     return ipAddr < tmpData;
}

bool IPv4Address::operator<(const IPv4Address& _rhs)const{
    return ipAddr < _rhs.data();
}

bool IPv4Address::operator>(const std::string& _rhs) const{
    return *this < _rhs.c_str();
}

bool IPv4Address::operator>(const char* _rhs) const{
    typeData tmpData;
    strToAddr(_rhs, tmpData);
    return ipAddr > tmpData;
}

bool IPv4Address::operator>(const IPv4Address& _rhs) const{
    return ipAddr < _rhs.data();
}

bool IPv4Address::operator<=(const std::string& _rhs) const{
    return !(this > _rhs);
}

bool IPv4Address::operator <=(const IPv4Address& _rhs) const{
    return !(this > _rhs);
}

bool IPv4Address::operator>=(const std::string& _rhs) const{
    return !(this < _rhs);
}

bool IPv4Address::operator >=(const IPv4Address& _rhs) const{
    return !(this < _rhs);
}
//TODO
/* *****[] Operator Check : OK*****
 * *****Pointer Ownership-check : OK******
 * Complete IPv4Address Class
 * Check IPv4Address Class
 * Add AddressIter Class
 * Sandboxie Terminal Prob
 */

IPv4Address IPv4Address::operator&(const std::string& _rhs) const{
    return *this & _rhs.c_str();
}

IPv4Address IPv4Address::operator&(const char* _rhs) const{
    IPv4Address varAddr = *this;
    varAddr &= _rhs;
    return varAddr;
}

IPv4Address IPv4Address::operator&(const IPv4Address& _rhs) const{
    IPv4Address varAddr = *this;
    varAddr &= _rhs;
    return varAddr;
}

IPv4Address& IPv4Address::operator&=(const std::string& _rhs){
    return *this &= _rhs.c_str();
}

IPv4Address& IPc4Address::operator&=(const char* _rhs){
    typeData tmpData;
    strToAddr(_rhs, tmpData);
    ipAddr &= tmpData;
    return *this;
}

IPv4Address& IPc4Address::operator&=(const IPv4Address& _rhs){
    ipAddr &= _rhs.data();
    return *this;
}

RENET_API friend std::ostream& operator<<(std::ostream& _output, const IPv4Address& _ip){
    return _output << addrToStr(*this);
}

RENET_API friend std::istream& operator>>(std::istream& _input, const IPv4Address& _ip){
    std::string strTmp;
    _input >> strTmp;
    strToAddr(strTmp, ipAddr);
    return _input;
}

IPv4Address::IPv4Type IPv4Address::getAddrType(){

}

bool IPv4Address::isAddrType(){

}

static void IPv4Address::strToAddr(std::string _ip, typeData& _addr){
    const char* str = _ip.c_str();
    int cnt = 0;

    if(!str || str == nullptr || *str == '\0')
        throw std::runtime_error("Invalid pointer access");
    for(uint8_t& i : _addr){
        i = strtoul(str, nullptr, 10);
        str = strchr(str, '.');
        if(!str || *str == '\0')
                break;
        str++;
        cnt++;
    }
    if(cnt < 3)
        throw std::runtime_error("Invalid IP String");
}

static std::string IPv4Address::addrToStr(const IPv4Address& _ip){
    std::ostringstream oss;
    for(size_t i = 0; i < 4; ++i)
        i < 3 ? oss << (unsigned)_ip.ipAddr[i] << "." : oss << (unsigned)_ip.ipAddr[i];
    return oss.str();
}
