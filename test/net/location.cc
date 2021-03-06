// Copyright (c) 2011, Robert Escriva
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of po6 nor the names of its contributors may be used
//       to endorse or promote products derived from this software without
//       specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// Google Test
#include <gtest/gtest.h>

// po6
#include "../include/po6/net/ipaddr.h"
#include "../include/po6/net/location.h"

#pragma GCC diagnostic ignored "-Wswitch-default"

namespace
{

TEST(LocationTest, CtorAndDtor)
{
    po6::net::location loc;
}

TEST(LocationTest, Comparison)
{
    // The addresses in this test were chosen to compare the same independent of
    // bite-order.
    po6::net::location locA("127.0.0.127", 1234);
    po6::net::location locB("127.1.1.127", 1234);

    EXPECT_LT(locA, locB);
    locA.address = po6::net::ipaddr("127.1.1.127");
    EXPECT_EQ(locA, locB);
    ++ locB.port;
    EXPECT_LT(locA, locB);
}

TEST(LocationTest, FromSockaddrIn)
{
    po6::net::ipaddr ip("127.0.0.1");
    sockaddr_in sa;
    ip.pack(&sa, 1234);

    po6::net::location loc(&sa);
    EXPECT_EQ(loc, po6::net::location("127.0.0.1", 1234));
}

TEST(LocationTest, FromSockaddrIn6)
{
    po6::net::ipaddr ip("::1");
    sockaddr_in6 sa;
    ip.pack(&sa, 1234);

    po6::net::location loc(&sa);
    EXPECT_EQ(loc, po6::net::location("::1", 1234));
}

TEST(LocationTest, FromSockaddrInCasted)
{
    po6::net::ipaddr ip("127.0.0.1");
    sockaddr_in sa;
    ip.pack(&sa, 1234);

    po6::net::location loc(reinterpret_cast<sockaddr*>(&sa), sizeof(sockaddr_in));
    EXPECT_EQ(loc, po6::net::location("127.0.0.1", 1234));
}

TEST(LocationTest, FromSockaddrIn6Casted)
{
    po6::net::ipaddr ip("::1");
    sockaddr_in6 sa;
    ip.pack(&sa, 1234);

    po6::net::location loc(reinterpret_cast<sockaddr*>(&sa), sizeof(sockaddr_in6));
    EXPECT_EQ(loc, po6::net::location("::1", 1234));
}

} // namespace
