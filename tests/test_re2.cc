#include <gtest/gtest.h>

#include "../re2/re2/re2.h"
#include "../src/re2-runner-lib.h"

TEST(Re2RunnerTest, test0) {
  std::string pattern = "(?:(a)|()|(b))+";
  std::string s = "aa";
  run_and_print_match_info(pattern, s);
}

TEST(Re2RunnerTest, test1) {
  std::string pattern = "((a||b)*)+";
  std::string s = "ab";
  run_and_print_match_info(pattern, s);
}

TEST(Re2RunnerTest, test2) {
  std::string pattern = "(a*)+";
  std::string s = "aa";
  run_and_print_match_info(pattern, s);
}

TEST(Re2RunnerTest, test3) {
  std::string pattern = "(a+b+)+";
  std::string s = "abab";
  run_and_print_match_info(pattern, s);
}

TEST(Re2RunnerTest, test4) {
  std::string pattern = "(?:()|a)*";
  std::string s = "aa";
  run_and_print_match_info(pattern, s);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}