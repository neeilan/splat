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
  EXPECT_TRUE(summary.output_set);
  EXPECT_FALSE(summary.exit_code_set);

  EXPECT_EQ(src.str(), summary.source);
  EXPECT_EQ(output, summary.output);
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
  EXPECT_TRUE(summary.output_set);
  EXPECT_FALSE(summary.exit_code_set);

  EXPECT_EQ(src.str(), summary.source);
  EXPECT_EQ(output, summary.output);
}

TEST(TestfileSummaryTest, Snippets) {
  osstream tf;

  tf << "a = [1]"     << endl
     << "b = a[3]"    << endl
     << "%snippet \"IndexError\""
     << endl;

  std::istringstream testfile(tf.str());
  Summary summary = Testfile::parse(testfile);

  osstream src;
  src << "a = [1]"   << endl
      << "b = a[3]"  << endl;

  EXPECT_FALSE(summary.parse_failed);
  EXPECT_FALSE(summary.output_set);
  EXPECT_FALSE(summary.exit_code_set);

  EXPECT_EQ(src.str(), summary.source);
  EXPECT_EQ(1, summary.snippets.size());
  EXPECT_EQ("IndexError", summary.snippets[0]);
}
