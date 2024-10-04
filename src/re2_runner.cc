#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../re2/re2/re2.h"
#include "absl/log/initialize.h"

/**
 * Check if `byte` starts a UTF-8 codepoint.
 *
 * @param byte The byte to check.
 * @return True if `byte` starts a UTF-8 codepoint, false otherwise.
 */
#define is_utf8_start_byte(byte) \
  ((byte & TWO_LEADING_BITS) != UTF8_NONSTART_BYTE_PREFIX)

// Binary: 1100
#define TWO_LEADING_BITS 0xC0
// Binary: 0100
#define UTF8_NONSTART_BYTE_PREFIX 0x80

/**
 * Count the number of UTF-8 codepoints between `begin` and `end`.
 *
 * Note: `begin` and `end` should be pointers to parts of the same C-style
 * string.
 *
 * @param begin A pointer to the first character of the string.
 * @param end A pointer to the character after the last character of the string.
 */
std::size_t utf8_distance(const char *begin, const char *end) {
  int ncodepoints = 0;
  for (const char *c = begin; c < end; c++) {
    if (is_utf8_start_byte(*c)) {
      ncodepoints++;
    }
  }
  return ncodepoints;
}

/**
 * Read the content of a file.
 *
 * @param filename The name of the file to read.
 * @return The content of the file as a string.
 */
extern std::string read_file(const char *filename) {
  std::ifstream input_file_stream(filename);
  assert(input_file_stream.is_open());
  std::stringstream buffer;
  buffer << input_file_stream.rdbuf();
  return buffer.str();
}

/**
 * Print match information in TOML format.
 *
 * @param s The input string.
 * @param submatch The array of submatches.
 * @param nsubmatch The number of capture groups + 1 (for the whole match).
 */
void print_match_info(const std::string &s, std::string_view *submatch,
                      int nsubmatch) {
  std::cout << "[match_1]\n\n";
  for (int i = 0; i < nsubmatch; i++) {
    std::size_t ncodepoints = utf8_distance(
        submatch[i].data(), submatch[i].data() + submatch[i].size());
    std::size_t start_index = utf8_distance(s.data(), submatch[i].data());
    std::size_t end_index = start_index + ncodepoints;
    std::cout << "span = [" << start_index << ", " << end_index << "]\n"
              << "str = '''" << submatch[i] << "'''\n\n";
  }
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
  std::cout << "[regex]\npattern = '''" << pattern << "'''\n";
  std::cout << "str = '''" << s << "'''\n\n";

  RE2 regex(pattern);
  std::size_t nsubmatch = regex.NumberOfCapturingGroups() + 1;
  std::string_view *submatch = new std::string_view[nsubmatch];
  std::size_t startpos = 0, endpos = s.size();

  if (regex.Match(s, startpos, endpos, RE2::UNANCHORED, submatch, nsubmatch)) {
    print_match_info(s, submatch, nsubmatch);
  } else {
    std::cout << "# no match\n\n";
  }

  return EXIT_SUCCESS;
}