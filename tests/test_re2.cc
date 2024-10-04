#include <gtest/gtest.h>

#include "../src/re2_runner.h"

TEST(Re2RunnerTest, test_match) {
  RE2 *regex = new RE2("(a|()|b)+");
  absl::string_view input_text("abab");
  int nsubmatches;
  absl::string_view *submatch;
  ASSERT_TRUE(match(regex, input_text, &nsubmatches, &submatch));
  delete[] submatch;
  delete regex;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}