#include <gtest/gtest.h>

#include "../src/re2_runner.h"

TEST(Re2RunnerTest, test_match) {
  RE2 *regex = new RE2("(a|()|b)+");
  absl::string_view input_text("ab");
  int nsubmatches;
  absl::string_view *submatch;
  ASSERT_TRUE(match(regex, input_text, &nsubmatches, &submatch));
  EXPECT_EQ(nsubmatches, 4);
  EXPECT_STREQ(submatch[0].data(), "ab");
  EXPECT_STREQ(submatch[1].data(), "a");
  EXPECT_STREQ(submatch[2].data(), "");
  EXPECT_STREQ(submatch[3].data(), "b");
  delete[] submatch;
  delete regex;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}