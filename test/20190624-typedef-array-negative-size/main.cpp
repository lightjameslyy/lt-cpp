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
    //typedef char T_must_be_complete_type[-1];
    assert(-1 > 0);
    return 0;
}
