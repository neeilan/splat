#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "testfile.h"

using Testfile::Summary;
using std::endl;

TEST(TestfileSummaryTest, SimpleSummary) {
  std::ostringstream tf;

  tf << "a = 5" << endl
     << "b = 10" << endl
     << "print(a+b)" << endl
     << "%output" << endl
     << "15" << endl
     << "%output";

  std::istringstream testfile(tf.str());
  Summary summary = Testfile::parse(testfile);

  std::string source = "a = 5\nb = 10\nprint(a+b)\n";
  std::string output = "15\n";

  EXPECT_FALSE(summary.parse_failed);

  EXPECT_EQ(source, summary.source);

  EXPECT_TRUE(summary.output_set);
  EXPECT_EQ(output, summary.output);

  EXPECT_FALSE(summary.exit_code_set);
}
