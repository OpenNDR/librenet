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

//Cxx Standard Headers
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <sstream>
#include <iterator>

#ifndef RENET_HW_ADDRESS_H
#define RENET_HW_ADDRESS_H

namespace Renet{
    template <size_t szT, typename typeData = uint8_t>
    class HWAddress{
    public:
        typedef typeData* iterator;
        typedef const typeData* const_iterator;

        enum HWType{
            UNICAST,
            MULTICAST,
            BROADCAST
        };

        static const HWAddress<szT, typeData> broadcast;

        explicit HWAddress(typeData (&_hw)[szT]){
            (_hw&&_hw!=nullptr) ? std::copy(_hw, _hw + szT, hwAddr) : throw std::runtime_error("Invalid pointer access");
        }
        explicit HWAddress(const std::string& _hw){
             HWAddress(_hw.c_str());
        }
        explicit HWAddress(const char* _hw){
            (_hw&&_hw!=nullptr) ? strToAddr(_hw, hwAddr) : throw std::runtime_error("Invalid pointer access");
        }
        HWAddress(const HWAddress<szT>& _hw){
            (_hw.hwAddr&&_hw.hwAddr!=nullptr) ? std::copy(_hw.begin(), _hw.end(), hwAddr) : throw std::runtime_error("Invalid pointer access");
        }

        //STL-Compatibility
        iterator begin(){
            return hwAddr;
        }
        const_iterator begin() const{
            return hwAddr;
        }
        iterator end(){
            return hwAddr + szAddr;
        }
        const_iterator end() const{
            return hwAddr + szAddr;
        }
        size_t len() const{
            return szAddr;
        }
        size_t size() const{
            return szAddr;
        }
        std::string to_string() const{
            return addrToString(*this);
        }

        //Operator overloading
        HWAddress<szT>& operator=(const HWAddress<szT>& _rhs){
            std::copy(_rhs.begin(), _rhs.end(), hwAddr);
            return *this;
        }
        typeData operator[](size_t i) const{
            return begin()[i];
        }
        typeData& operator[](size_t i){
            return begin()[i];
        }
        bool operator==(const HWAddress& _rhs) const{
            return std::equal(begin(), end(), _rhs.begin());
        }
        bool operator!=(const HWAddress& _rhs) const{
            return !(*this == _rhs);
        }
        HWAddress<szT> operator&(const HWAddress<szT>& _rhs) const{
            HWAddress<szT> varAddr = *this;
            for(size_t i = 0; i < szT; ++i)
                varAddr[i] &= _rhs[i];
            return varAddr;
        }//HWAddress Masking (& Operation)
        void operator&=(const HWAddress<szT>& _rhs){
            for(size_t i = 0; i < szT; ++i)
                hwAddr[i] &= _rhs[i];
        }//HWAddress Masking (&= Operation)
        RENET_API friend std::ostream& operator<<(std::ostream& _output, const HWAddress& _hw){
            return _output << addrToString(_hw);
        }

        HWType getAddrType() const{
            if(*this==broadcast)
                return HWType::BROADCAST;
            if(*begin() & 0x01)
                return HWType::MULTICAST;
            return HWType::UNICAST;
        }
        bool isAddrType(HWType _type) const{
            return getAddrType() == _type;
        }
        template<typename Iterator>
        Iterator copy(Iterator _target) const{
           for(typeData i : hwAddr)
               *_target++ = i;
           return _target;
        }

    private:
        typeData hwAddr[szT];
        static const size_t szAddr = szT;

        inline void strToAddr(std::string _hw, typeData (&_addr)[szT]){
            const char* str = _hw.c_str();
            int cnt = 0;

            if(!str || str == nullptr || *str == '\0')
                throw std::runtime_error("Invalid pointer access");
            for(typeData& i : _addr){
                i = strtoul(str, nullptr, 16);
                str = strchr(str, ':');
                if(!str || *str == '\0')
                        break;
                str++;
                cnt++;
            }
            if(cnt < 5)
                throw std::runtime_error("Invalid MAC String");
        }
        static std::string addrToString(const HWAddress<szT>& _hw){
            std::ostringstream oss;
            oss << std::hex;
            for(size_t i = 0; i < szT; ++i){
                if(_hw.hwAddr[i] < 0x10)
                    oss << '0';
                i < szT -1 ? oss << (unsigned)_hw.hwAddr[i] << ':' : oss << (unsigned)_hw.hwAddr[i];
            }
            return oss.str();
        }

        static HWAddress<szT> buildBroadcastAddr(){
            typeData tmpAddr[szT];
            for(size_t i = 0; i < szT; ++i)
                tmpAddr[i] = 0xff;
            return HWAddress<szT>(tmpAddr);
        }
    };

    template <size_t szT, typename typeData>
    const HWAddress<szT, typeData> HWAddress<szT, typeData>::broadcast = buildBroadcastAddr();

}//Namespace Renet

namespace std {
    template<size_t szT> struct hash<Renet::HWAddress<szT>> {
         size_t operator()(const Renet::HWAddress<szT>& _hw) const {
             return std::hash<std::string>()(_hw.to_string());
         }
    };
}

#endif // RENET_HW_ADDRESS_H
