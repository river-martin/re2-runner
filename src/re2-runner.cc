#include <cassert>
#include <fstream>
#include <iostream>

#include "re2-runner-lib.h"
#include "utils.h"

int main(int argc, const char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <pattern-file> <input-str-file>\n";
    return EXIT_FAILURE;
  }

  absl::InitializeLog();

  std::string pattern = utils::read_file(std::string(argv[1]));
  std::string s = utils::read_file(std::string(argv[2]));

  run_and_print_match_info(pattern, s);

  return EXIT_SUCCESS;
}