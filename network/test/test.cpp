#include <gtest/gtest.h>
#include "lnp_lt.h"

TEST(lnp, isHostBigEndian) {
    isHostBigEndian();
}

TEST(lnp, byteOrderConversion) {
    unsigned int x = 0x12345678;

    unsigned int y = htonl(x);
    unsigned char* p = (unsigned char*)&y;
    ASSERT_EQ(y, 0x78563412);

    x = ntohl(y);
    ASSERT_EQ(x, 0x12345678);
}

TEST(lnp, addrConversion) {
    unsigned int addr = inet_addr("192.168.0.100");
    printf("addr=%u\n", ntohl(addr));

    struct in_addr ipaddr;
    ipaddr.s_addr = addr;
    printf("%s\n", inet_ntoa(ipaddr));
}

