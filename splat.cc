#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h> // for atoi
#include <vector>

#include "exec.h"

bool starts_with(const std::string & s, const std::string & prefix) {
  if (s.size() < prefix.size()) return false;
  return s.substr(0, prefix.size()) == prefix;
}

const std::string trim_prefix(const std::string & s, const std::string & prefix) {
  return s.substr(prefix.size());
}

int main() {
  std::ifstream f("test.splat");
  // std::string line;

  int expected_exit_code = 0;
  std::ostringstream source;
  std::ostringstream expected_output;
  size_t line_num = 0;
  std::vector<std::string> expected_snippets;

  for( std::string line; getline( f, line ); )
  {
    line_num++;
    if (starts_with(line, "%expect-exit-code")) {
      expected_exit_code = atoi( trim_prefix(line, "%expect-exit-code").c_str() );   
    } else if (starts_with(line, "%begin-expected-output")) {
      for (std::string line; getline( f, line ) && !starts_with(line, "%end-expected-output"); ) {
        line_num++;
        expected_output << line << std::endl;
      }
    } else if (starts_with(line, "%expect-output-snippet")) {
      std::string content = trim_prefix(line, "%expect-output-snippet");
      if (std::count(content.begin(), content.end(), '"') < 2) {
        std::cout << "ERROR: Expected snippet must be enclosed within double quotes. Found: " << content << std::endl;
        return -1;
      }
      expected_snippets.push_back(content.substr(content.find("\"") + 1, content.rfind("\"") - 2) );
    } else {
      source << line << std::endl;
    }
  }

  std::cout << "SOURCE: " << std::endl << source.str();
  std::cout << "EXPECTED OUTPUT: " << std::endl << expected_output.str();
  std::cout << "EXPECTED EXIT CODE: " << expected_exit_code << std::endl;


  std::ofstream outfile (".splat_source");
  outfile << source.str();
  outfile.close(); 

  std::string command = "/Users/neeilanselvalingam/Desktop/neeilang/bin/neeilang .splat_source 2>&1";
  std::string output = execute(command);
  std::cout << "ACTUAL OUTPUT: " << std::endl << output;

  if (output != expected_output.str()) {

  }

  return 0;
}
