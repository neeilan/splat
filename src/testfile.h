#ifndef _SPLAT_TESTFILE_H_ 
#define _SPLAT_TESTFILE_H_ 

#include <string>
#include <vector>
#include <fstream>

namespace Testfile {

  struct Summary {
    std::string source;
    bool output_set;
    std::string output;
    bool exit_code_set;
    int exit_code;
    std::vector<std::string> snippets;
    int parse_failed = 0;
    std::string parse_error;
  };

  Testfile::Summary parse(std::ifstream & f);

}

#endif // _SPLAT_TESTFILE_H_ 
