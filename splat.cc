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

int main(int argc, char * argv[]) {
  if (argc < 2) {
    std::cout << "Usage: splat <run script> <test program>" << std::endl;
    return 0; // TODO: What code should be returned here?
  }
  std::ifstream f(argv[1]);

  int expected_exit_code = 0;
  std::ostringstream source;
  std::ostringstream expected_output;
  size_t line_num = 0;
  std::vector<std::string> expected_snippets;
  bool test_output = false;

  for( std::string line; getline( f, line ); )
  {
    line_num++;
    if (starts_with(line, "%expect-exit-code")) {
      expected_exit_code = atoi( trim_prefix(line, "%expect-exit-code").c_str() );   
    } else if (starts_with(line, "%begin-expected-output")) {
      test_output = true;
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

  std::cout << "EXPECTED EXIT CODE: " << expected_exit_code << std::endl;

  const char * srcfile = ".splat_source";
  std::ofstream outfile (srcfile);
  outfile << source.str();
  outfile.close(); 

  std::string command = "/usr/bin/python .splat_source 2>&1";
  std::string output = execute(command);

  remove(srcfile);

  bool has_error = false;
  if (test_output && output != expected_output.str()) {
    has_error = true;
    std::cout << "Expected and actual outputs do not match." << std::endl;
    std::cout << "EXPECTED:" << std::endl << expected_output.str() << std::endl;
    std::cout << "GOT:" << std::endl << output << std::endl;
  }

  bool missing_snippet = false;
  for (const std::string & snippet : expected_snippets) {
    if (output.find(snippet) == -1) {
      missing_snippet = has_error = true;
      std::cout << "DID NOT FIND SNIPPET: '" << snippet << "'" << std::endl;
    }
  }
  if (missing_snippet) {
    std::cout << "OUTPUT:" << std::endl << output << std::endl;
  }

  if (!has_error) {
    std::cout << "OK" << std::endl;
  }

  return 0;
}
