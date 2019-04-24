#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
using namespace std;
using namespace boost::filesystem;

int main(int argc, char* argv[]) {

    string s = "./";

    path p(s);  // avoid repeated path construction below
    p += "/main.cpp";

    if (exists(p)) {  // does path p actually exist?
        if (is_regular_file(p))        // is path p a regular file?
            cout << p << " size is " << file_size(p) << '\n';

        else if (is_directory(p))      // is path p a directory?
            cout << p << " is a directory\n";

        else
            cout << p << " exists, but is not a regular file or directory\n";
    } else
        cout << p << " does not exist\n";

    return 0;
}
