#include "re2_runner.h"

#include <cassert>
#include <fstream>
#include <sstream>

extern std::string read_file(const char *filename) {
  std::ifstream input_file_stream(filename);
  assert(input_file_stream.is_open());
  std::stringstream buffer;
  buffer << input_file_stream.rdbuf();
  return buffer.str();
}

extern std::size_t utf8_distance(const char *begin, const char *end) {
  int ncodepoints = 0;
  for (const char *c = begin; c < end; c++) {
    if (is_utf8_start_byte(*c)) {
      ncodepoints++;
    }
  }
  return ncodepoints;
}

extern bool match(RE2 *regex, absl::string_view input_text, int *nsubmatches,
                  absl::string_view **submatch) {
  *nsubmatches = regex->NumberOfCapturingGroups() + 1;
  *submatch = new absl::string_view[*nsubmatches];
  if (regex->Match(input_text, 0, input_text.size(), RE2::UNANCHORED, *submatch,
                   *nsubmatches)) {
    return true;
  } else {
    return false;
  }
}