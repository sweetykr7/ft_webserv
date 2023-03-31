#include <dirent.h>
#include <string>
#include <vector>

std::vector<std::string> get_directory_list(const std::string& dir_path) {
    std::vector<std::string> result;
    DIR* dir = opendir(dir_path.c_str());
    if (dir == NULL) {
        return result;
    }

    dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        std::string filename = entry->d_name;
        if (filename != "." && filename != "..") {
            result.push_back(filename);
        }
    }

    closedir(dir);
    return result;
}


#include <iostream>
#include <sstream>
// #include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// #include "httplib.h"

// using namespace httplib;

int main() {
	
	std::string directory = "./test_dir";
	std::vector<std::string> files = get_directory_list(directory);
	std::stringstream ss;
	ss << "<html><body>";
	std::vector<std::string>::iterator it = files.begin();
	for (;it!=files.end();it++) {
		ss << "<a href=\"" << *it << "\">" << *it << "</a><br>";
	}
	ss << "</body></html>";

	std::cout << ss.str() << std::endl;

    
}