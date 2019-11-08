#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>

#include "glog/logging.h"
#include "glog/raw_logging.h"

#include "tools.h"

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    // output to stderr
    FLAGS_logtostderr = 1;

    // init
    google::InitGoogleLogging(argv[0]);

    // set minloglevel
    // INFO: 0
    // WARNING: 1
    // ERROR: 2
    // FATAL: 3
    FLAGS_minloglevel = 0;
    printf("level INFO: \n");

    LOG(INFO) << "0 info";
    LOG(WARNING) << "0 warning";
    LOG(ERROR) << "0 error";

    FLAGS_minloglevel = 1;
    printf("level WARNING: \n");

    LOG(INFO) << "1 info";
    LOG(WARNING) << "1 warning";
    LOG(ERROR) << "1 error";

    FLAGS_minloglevel = 2;
    printf("level ERROR: \n");

    LOG(INFO) << "2 info";
    LOG(WARNING) << "2 warning";
    LOG(ERROR) << "2 error";

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
