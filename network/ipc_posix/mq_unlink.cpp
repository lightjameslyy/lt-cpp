#include "lnp_lt.h"

using namespace lt;

int main(int argc, char* argv[]) {

    int ret = mq_unlink("/abc");
    if (ret == -1)
        err::Exit("mq_unlink");

    return 0;
}
