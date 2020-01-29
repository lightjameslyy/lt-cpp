#include "lnp_lt.h"

namespace lt {

bool isHostBigEndian() {
    unsigned int val = 0x12345678;
    unsigned char* p = (unsigned char*)&val;
    return p[0] == 0x12;
}

}   // namespace lt
