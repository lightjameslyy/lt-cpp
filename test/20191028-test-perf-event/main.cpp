#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <unistd.h>
#include <cstring>
#include <sys/ioctl.h>
#include <linux/perf_event.h>
#include <asm/unistd.h>

#include <iostream>
#include <vector>
#include <chrono>

#include <omp.h>

#include "tools.h"

using namespace std;
using namespace chrono;

static long
perf_event_open(struct perf_event_attr *hw_event, pid_t pid,
                int cpu, int group_fd, unsigned long flags) {
    int ret;

    ret = syscall(__NR_perf_event_open, hw_event, pid, cpu,
                  group_fd, flags);

    if (ret == -1) {
        fprintf(stderr, "Error opening leader %llx\n", hw_event->config);
        exit(EXIT_FAILURE);
    }

    return ret;
}

// config: PERF_COUNT_HW_INSTRUCTIONS, PERF_COUNT_HW_CACHE_MISSES, PERF_COUNT_HW_CACHE_REFERENCES ...
int getEventAttr(uint64_t config) {
    struct perf_event_attr pe;
    memset(&pe, 0, sizeof(struct perf_event_attr));
    pe.type = PERF_TYPE_HARDWARE;
    pe.size = sizeof(struct perf_event_attr);
    pe.config = config;
    pe.disabled = 1;
    pe.exclude_kernel = 1;
    pe.exclude_hv = 1;

    int fd = perf_event_open(&pe, 0, -1, -1, 0);

    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
    ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);

    return fd;
}

void getPerfCountAndClose(int fd, long long *count_ptr) {
    ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
    read(fd, count_ptr, sizeof(long long));
    close(fd);
}

int main(int argc, char *argv[]) {

    string hostName, Ip;
    if (GetHostInfo(hostName, Ip)) {
    }
    cout << "hostname: " << hostName << ", ip: " << Ip << endl;

    auto start = system_clock::now();

    int fd1 = getEventAttr(PERF_COUNT_HW_CACHE_REFERENCES);
    int fd2 = getEventAttr(PERF_COUNT_HW_CACHE_MISSES);

    int max_val = 0;
    #pragma omp parallel for reduction(max: max_val)
    for (int i = 0; i < 1000; ++i) {
        max_val = i;
    }

    cout << "max_val: " << max_val << endl;
    assert(max_val == 999);

    long long count1, count2;
    getPerfCountAndClose(fd1, &count1);
    getPerfCountAndClose(fd2, &count2);

    printf("cache references: %lld \n", count1);
    printf("cache misses: %lld \n", count2);

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end-start);
    cout << "time: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s\n";
    return 0;
}
