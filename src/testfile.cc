#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h> // for atoi
#include <vector>

#include "strutil.h"
#include "testfile.h"
#include "directives.h"

using Directives::COMMENT;
using Directives::EXPECT_OUTPUT;
using Directives::EXPECT_SNIPPET;
using Directives::EXPECT_EXIT_CODE;

Testfile::Summary Testfile::parse(std::ifstream & f) {
  Summary summary;

  std::ostringstream source;
  std::ostringstream output;
  std::vector<std::string> snippets;

  for( std::string line; getline( f, line ); )
  {
    if (starts_with(line, EXPECT_EXIT_CODE)) {
      summary.exit_code = atoi( trim_prefix(line, EXPECT_EXIT_CODE).c_str() );   
      summary.exit_code_set = true;
    } else if (starts_with(line, EXPECT_OUTPUT)) {
      summary.output_set = true;
      for (std::string line; getline( f, line ) && !starts_with(line, EXPECT_OUTPUT); ) {
        output << line << std::endl;
      }
    } else if (starts_with(line, EXPECT_SNIPPET)) {
      std::string content = trim_prefix(line, EXPECT_SNIPPET);
      if (std::count(content.begin(), content.end(), '"') < 2) {
        summary.parse_failed = true;
        summary.parse_error = "Expected snippet not enclosed in double quotes: " + content;
        return summary;
      }
      snippets.push_back(content.substr(content.find("\"") + 1, content.rfind("\"") - 2) );
    } else if (starts_with(line, COMMENT)) {
      // Ignore
    }
     else {
      source << line << std::endl;
    }
  }

  summary.source = source.str();
  summary.output = output.str();
  return summary;
}
