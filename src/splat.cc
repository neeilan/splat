#include <fstream>
#include <iostream>
#include <string>

#include "testfile.h"
#include "exec.h"

using std::cout;
using std::endl;

int test(std::ifstream & f) {
  Testfile::Summary tf = Testfile::parse(f);

  const char * srcfile = ".splat_source";
  std::ofstream outfile (srcfile);
  outfile << tf.source;
  outfile.close(); 

  std::string command = "/usr/bin/python .splat_source 2>&1";
  std::string output = execute(command);

  remove(srcfile);

  bool has_error = false;
  if (tf.output_set && output != tf.output) {
    has_error = true;
    cout << "Expected and actual outputs do not match." << std::endl;
    cout << "EXPECTED:" << std::endl << tf.output << std::endl;
    cout << "GOT:" << std::endl << output << std::endl;
  }

  bool missing_snippet = false;
  for (const std::string & snippet : tf.snippets) {
    if (output.find(snippet) == std::string::npos) {
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
