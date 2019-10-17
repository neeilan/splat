#ifndef _SPLAT_TESTFILE_H_ 
#define _SPLAT_TESTFILE_H_ 

#include <string>
#include <vector>
#include <istream>

namespace Testfile {

  struct Summary {
    std::string source;
    std::string output;
    int exit_code;
    std::vector<std::string> snippets;
    std::string parse_error;

    bool parse_failed = false;
    bool output_set = false;
    bool exit_code_set = false;
  };

  Testfile::Summary parse(std::istream & f);

}

#endif // _SPLAT_TESTFILE_H_ 
