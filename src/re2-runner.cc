#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

#include "re2-runner-lib.h"

/**
 * Read the content of a file.
 *
 * @param filename The name of the file to read.
 * @return The content of the file as a string.
 */
std::string read_file(const char *filename) {
  std::ifstream input_file_stream(filename);
  assert(input_file_stream.is_open());
  std::stringstream buffer;
  buffer << input_file_stream.rdbuf();
  return buffer.str();
}

int main(int argc, const char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <pattern-file> <input-str-file>\n";
    return EXIT_FAILURE;
  }

  // Necessary to avoid a warning about logging before calling
  // absl::InitializeLog
  absl::InitializeLog();

  std::string pattern = read_file(argv[1]);
  std::string s = read_file(argv[2]);

  run_and_print_match_info(pattern, s);

  return EXIT_SUCCESS;
}