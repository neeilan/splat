#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "testfile.h"

using Testfile::Summary;

using osstream = std::ostringstream;
using std::endl;

TEST(TestfileEdgeCasesTest, EmptyFile) {
  osstream tf;
  std::istringstream testfile("");
  Summary summary = Testfile::parse(testfile);

  EXPECT_FALSE(summary.parse_failed);
  EXPECT_FALSE(summary.output_set);
  EXPECT_FALSE(summary.exit_code_set);

  EXPECT_EQ("", summary.source);
  EXPECT_EQ("", summary.output);
}

TEST(TestfileEdgeCasesTest, NoSource) {
  osstream tf;

  tf << "%output"     << endl
     << "15"          << endl
     << "%output"     << endl;

  std::istringstream testfile(tf.str());
  Summary summary = Testfile::parse(testfile);


  EXPECT_FALSE(summary.parse_failed);
  EXPECT_TRUE(summary.output_set);
  EXPECT_FALSE(summary.exit_code_set);

  EXPECT_EQ("", summary.source);
  EXPECT_EQ("15\n", summary.output);
}
