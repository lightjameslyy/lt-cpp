#include "lnp_lt.h"

bool isHostBigEndian() {
    unsigned int val = 0x12345678;
    unsigned char* p = (unsigned char*)&val;
    return p[0] == 0x12;
}
