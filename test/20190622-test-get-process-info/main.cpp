#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <cassert>

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

#include <boost/algorithm/string.hpp>

typedef std::unordered_map<std::string, std::string> proc_status_t;

void get_process_info(pid_t pid, proc_status_t & proc_status) {
    // 1. get process status file name
    std::string psfilename = "/proc/" + std::to_string(pid) + "/status";
    // 2. open process status file
    std::ifstream psfile(psfilename);
    assert(psfile.is_open());
    // 3. parse to proc_status
    std::string line;
    while (std::getline(psfile, line)) {
        std::vector<std::string> kv;
        boost::split(kv, line, boost::is_any_of(":"));
        assert(kv.size() == 2);
        boost::trim(kv[1]);
        //std::cout << kv[0] << ":[" << kv[1] << "]" << std::endl;
        proc_status[kv[0]] = kv[1];
    }
    psfile.close();
}

int main(int argc, char *argv[]) {
    pid_t pid = getpid();
    if (argc > 1) {
        pid = atoi(argv[1]);
    }
    std::cout << "watch pid: " << pid << ", self pid: " << getpid() << std::endl;
    proc_status_t proc_status;
    std::vector<int> mem;
    char ch;
    while (1) {
        get_process_info(pid, proc_status);
        std::cout << "memory usage: " << proc_status["VmRSS"] << std::endl;
        std::cout << "continue increasing memory usage? (Y/N) ";
        std::cin.get(ch);
        if (ch == 'N' || ch == 'n') 
            break;
        else {
            mem.resize(mem.size() + (1 << 20));
            std::cout << "mem.size: " << mem.size()*4/1024/1024 << "MB" << std::endl;
        }
    }
    return 0;
}
