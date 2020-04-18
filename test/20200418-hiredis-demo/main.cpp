#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>

#include "tools.h"
#include <hiredis/hiredis.h>

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    // redisContext* c = redisConnect("hostname", port);
    redisContext* c = redisConnect("k8s-master01", 6379);
    if (c != NULL && c->err) {
        printf("Error: %s\n", c->errstr);
        if (c) {
            redisFree(c);
            c = nullptr;
        }
        exit(-1);
    } else {
        printf("Connected to Redis\n");
    }

    redisReply* reply;
    // reply = (redisReply*)redisCommand(c, "auth password");
    reply = (redisReply*)redisCommand(c, "auth 123123");
    printf("%s\n", reply->str);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(c, "set k2 v2");
    printf("%s\n", reply->str);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(c, "get k2");
    printf("%s\n", reply->str);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(c, "keys *");
    size_t nelem = reply->elements;
    printf("keys: ");
    for (int i = 0; i < nelem; ++i)
        printf("%s ", reply->element[i]->str);
    printf("\n");
    freeReplyObject(reply);

    redisFree(c);

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
