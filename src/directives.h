#ifndef _SPLAT_DIRECTIVES_H_ 
#define _SPLAT_DIRECTIVES_H_ 

#include <string>

namespace Directives {
  const std::string COMMENT = "%%";
  const std::string EXPECT_OUTPUT = "%output";
  const std::string EXPECT_SNIPPET = "%snippet";
  const std::string EXPECT_EXIT_CODE = "%exit";
  const std::string SRC_EXTENSION = "%src-extension";
}

#endif // _SPLAT_DIRECTIVES_H_ 
