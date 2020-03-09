#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <tuple>
#include <sys/wait.h>
#include <cstring>

std::tuple<std::string, int> execute(const std::string & command) {
    const char* cmd = command.c_str();
    std::array<char, 128> buffer;
    std::string output;
    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        output += buffer.data();
    }
    
    int exit_code = pclose(pipe);
    if (WIFSIGNALED(exit_code) || WIFSTOPPED(exit_code)) {
        throw std::runtime_error(std::string("process received signal ")
            + strsignal(WIFSIGNALED(exit_code) ? WTERMSIG(exit_code) : WSTOPSIG(exit_code)));
    }
    else if (WIFEXITED(exit_code)) {
        exit_code = WEXITSTATUS(exit_code);
    }
    else {
        throw std::runtime_error("process terminated, but neither successfully nor by signal?");
    }
    
    return std::make_tuple(output, exit_code);
}
