#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h> // for atoi
#include <vector>

#include "directives.h"
#include "exec.h"
#include "strutil.h"

using Directives::EXPECT_OUTPUT;
using Directives::EXPECT_SNIPPET;

using std::cout;
using std::endl;

int test(std::ifstream & f) {
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
    } else if (starts_with(line, EXPECT_OUTPUT)) {
      test_output = true;
      for (std::string line; getline( f, line ) && !starts_with(line, EXPECT_OUTPUT); ) {
        line_num++;
        expected_output << line << std::endl;
      }
    } else if (starts_with(line, EXPECT_SNIPPET)) {
      std::string content = trim_prefix(line, EXPECT_SNIPPET);
      if (std::count(content.begin(), content.end(), '"') < 2) {
        cout << "ERROR: Expected snippet must be enclosed within double quotes. "
             << "Found: " << content << std::endl;
        return 1;
      }
      expected_snippets.push_back(content.substr(content.find("\"") + 1, content.rfind("\"") - 2) );
    } else {
      source << line << std::endl;
    }
  }

  cout << "EXPECTED EXIT CODE: " << expected_exit_code << std::endl;

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
    cout << "Expected and actual outputs do not match." << std::endl;
    cout << "EXPECTED:" << std::endl << expected_output.str() << std::endl;
    cout << "GOT:" << std::endl << output << std::endl;
  }

  bool missing_snippet = false;
  for (const std::string & snippet : expected_snippets) {
    if (output.find(snippet) == -1) {
      missing_snippet = has_error = true;
      cout << "DID NOT FIND SNIPPET: '" << snippet << "'" << std::endl;
    }
  }
  if (missing_snippet) {
    cout << "OUTPUT:" << std::endl << output << std::endl;
  }

  if (has_error) {
    return 1;
  }

  cout << "OK" << std::endl;
  return 0;
}
