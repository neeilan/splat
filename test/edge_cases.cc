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

TEST(TestfileEdgeCasesTest, UnterminatedSnippetQuotes) {
  osstream tf;

  tf << "%snippet \"text" << endl
     << "print(15)"       << endl
     << "print(15)"       << endl
     << "%output"         << endl;

  std::istringstream testfile(tf.str());
  Summary summary = Testfile::parse(testfile);


  EXPECT_TRUE(summary.parse_failed);
}

TEST(TestfileEdgeCasesTest, ExtraSnippetQuotes) {
  osstream tf;

  tf << "%snippet \"text1\"23\"" << endl
     << "print(15)"       << endl
     << "print(15)"       << endl
     << "%output"         << endl;

  std::istringstream testfile(tf.str());
  Summary summary = Testfile::parse(testfile);

  EXPECT_FALSE(summary.parse_failed);
  EXPECT_EQ(1, summary.snippets.size());
  EXPECT_EQ("text1\"23", summary.snippets[0]);
}
