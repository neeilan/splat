#include <fstream>
#include <iostream>
#include <string>

#include "testfile.h"
#include "exec.h"

using std::cout;
using std::endl;

int test(std::ifstream & f) {
  Testfile::Summary tf = Testfile::parse(f);

  std::string srcfile = ".splat_source" + tf.src_extension;
  std::ofstream outfile (srcfile.c_str());
  outfile << tf.source;
  outfile.close(); 

  std::string command = "./examples/bind_gcc.sh " + srcfile + " 2>&1";
  std::string output = execute(command);

  remove(srcfile.c_str());

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
