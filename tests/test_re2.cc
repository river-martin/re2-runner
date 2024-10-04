#include <gtest/gtest.h>

#include "../re2/re2/re2.h"

TEST(Re2RunnerTest, test_match) {
  RE2 r("(a|()|b)+");
  std::string_view s("abab");
  std::size_t nsubmatch = r.NumberOfCapturingGroups() + 1;
  std::string_view* submatch = new std::string_view[nsubmatch];
  std::size_t spos = 0, epos = s.length();
  ASSERT_TRUE(r.Match(s, spos, epos, RE2::UNANCHORED, submatch, nsubmatch));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}