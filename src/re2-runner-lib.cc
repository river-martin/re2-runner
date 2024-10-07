#include <iostream>
#include <string>

#include "../re2/re2/re2.h"

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

extern void print_match_info(const std::string &s, std::string_view *submatch,
                             int nsubmatch) {
  std::cout << "[match_1]\n\n";
  for (int i = 0; i < nsubmatch; i++) {
    std::cout << "[match_1.group_" << i << "]\n";
    std::size_t ncodepoints = utf8_distance(
        submatch[i].data(), submatch[i].data() + submatch[i].size());
    std::size_t start_index = utf8_distance(s.data(), submatch[i].data());
    std::size_t end_index = start_index + ncodepoints;
    std::cout << "span = [" << start_index << ", " << end_index << "]\n"
              << "str = '''" << submatch[i] << "'''\n\n";
  }
}

extern void run_and_print_match_info(const std::string &pattern,
                                     const std::string &s) {
  std::cout << "[regex]\npattern = '''" << pattern << "'''\n";
  std::cout << "str = '''" << s << "'''\n\n";

  RE2 regex(pattern);
  std::size_t nsubmatch = regex.NumberOfCapturingGroups() + 1;
  std::string_view *submatch = new std::string_view[nsubmatch];
  std::size_t spos = 0, epos = s.length();

  if (regex.Match(s, spos, epos, RE2::UNANCHORED, submatch, nsubmatch)) {
    print_match_info(s, submatch, nsubmatch);
  } else {
    std::cout << "# no match\n\n";
  }
}