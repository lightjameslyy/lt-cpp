/*
 * proccess per connection
 * using readline
 */

#include "lnp_lt.h"

using namespace lt;

int main(int argc, char* argv[]) {
    char host[100] = {0};
    if (gethostname(host, sizeof(host)) < 0)
        err::Exit("gethostname");

    struct hostent* hp;
    if ((hp = gethostbyname(host)) == NULL)
        err::Exit("gethostbyname");

    int i = 0;
    while (hp->h_addr_list[i] != NULL) {
        printf("%s\n", inet_ntoa(*(struct in_addr*)hp->h_addr_list[i]));
        ++i;
    }

    char ipStr[16] = {0};
    info::getlocalip(ipStr);
    printf("getlocalip: %s\n", ipStr);
}
