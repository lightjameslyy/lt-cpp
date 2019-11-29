#include <iostream>
#include <omp.h>
#include <vector>
#include <stdio.h>
#include <chrono>

#include <gflags/gflags.h>

#include "tools.h"

using namespace std;
using namespace chrono;

DEFINE_bool(happy, true, "is happy or not");
DEFINE_int64(num, 1LL << 60, "a big number");
DEFINE_string(message, "Hello World!", "a message");

int main(int argc, char* argv[]) {

    gflags::SetUsageMessage("test gflags");
    gflags::SetVersionString("1.0.0");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    cout << gflags::ProgramInvocationShortName() << ": " << FLAGS_message << endl;
    cout << "num: " << FLAGS_num << endl;
    cout << "I'm " << (FLAGS_happy ? "happy" : "not happy") << endl;

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";

    gflags::ShutDownCommandLineFlags();

    return 0;
}
