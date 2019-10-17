#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "testfile.h"

using Testfile::Summary;

using osstream = std::ostringstream;
using std::endl;

TEST(TestfileSummaryTest, SimpleSummary) {
  osstream tf;

  tf << "a = 5"       << endl
     << "b = 10"      << endl
     << "print(a+b)"  << endl
     << "%output"     << endl
     << "15"          << endl
     << "%output"     << endl;

  std::istringstream testfile(tf.str());
  Summary summary = Testfile::parse(testfile);

  osstream src;
  src << "a = 5"       << endl
      << "b = 10"      << endl
      << "print(a+b)"  << endl;

  std::string output = "15\n";

  EXPECT_FALSE(summary.parse_failed);

  EXPECT_EQ(src.str(), summary.source);

  EXPECT_TRUE(summary.output_set);
  EXPECT_EQ(output, summary.output);

  EXPECT_FALSE(summary.exit_code_set);
}

TEST(TestfileSummaryTest, MultipleOutputs) {
  osstream tf;

  tf << "a = 5"       << endl
     << "b = 10"      << endl
     << "print(a+b)"  << endl
     << "%output"     << endl
     << "15"          << endl
     << "%output"     << endl
     << "print(b)"    << endl
     << "%output"     << endl
     << "10"          << endl
     << "%output"     << endl;

  std::istringstream testfile(tf.str());
  Summary summary = Testfile::parse(testfile);

  osstream src;
  src << "a = 5"       << endl
      << "b = 10"      << endl
      << "print(a+b)"  << endl
      << "print(b)"    << endl;

  std::string output = "15\n10\n";

  EXPECT_FALSE(summary.parse_failed);

  EXPECT_EQ(src.str(), summary.source);

  EXPECT_TRUE(summary.output_set);
  EXPECT_EQ(output, summary.output);

  EXPECT_FALSE(summary.exit_code_set);
}
