/*
 * test getrlimit and setrlimit
 */

#include "lnp_lt.h"

using namespace lt;

int main(int argc, char* argv[]) {

    struct rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        err::Exit("getrlimit");
    printf("RLIMIT_NOFILE: %d\n", (int)rl.rlim_max);

    rl.rlim_cur = 2048;
    rl.rlim_max = 2048;
    if (setrlimit(RLIMIT_NOFILE, &rl) < 0)
        err::Exit("setrlimit");
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        err::Exit("getrlimit");
    printf("RLIMIT_NOFILE: %d\n", (int)rl.rlim_max);

    return 0;
}
