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

#ifndef RENET_MACROS_H
#define RENET_MACROS_H

    #if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
        #include <sys/param.h>
    #endif

    #if defined(_WIN32) && defined(_DYNAMIC)
        #define RENET_API __declspec(dllexport)
    #else
        #define RENET_API
    #endif

    #ifdef _MSC_VER
        #define RENET_DEBUG
        #define RENET_SECTION(name)
        #define RENET_ALIGN(size)
        #define RENET_PACK
        #define RENET_DEPRECATED(func)
        #define RENET_LFUNC
        #define RENET_NOEXCEPT
        #define RENET_EXPECT_T(x)
        #define RENET_EXPECT_F(x)
    #else
        #define RENET_DEBUG __attribute__ ((unused))
        #define RENET_SECTION(name) __attribute__ ((section (name)))
        #define RENET_ALIGN(size) __attribute__ ((aligned (size)))
        #define RENET_PACK __attribute__ ((packed))
        #define RENET_DEPRECATED(func) func __attribute__ ((deprecated))
        #define RENET_LFUNC inline
        #define RENET_NOEXCEPT noexcept
        #define RENET_EXPECT_T(x) __builtin_expect((x), 1)
        #define RENET_EXPECT_F(x) __builtin_expect((x), 0)
    #endif

#endif // RENET_MACROS_H
