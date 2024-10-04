#include "../re2/re2/re2.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "absl/log/initialize.h"

// 1100
#define TWO_LEADING_BITS 0xC0
// 0100
#define UTF8_NONSTART_BYTE_PREFIX 0x80

/**
 * Read the content of a file.
 *
 * @param filename The name of the file to read.
 * @return The content of the file as a string.
 */
std::string read_file(const char *filename)
{
  std::ifstream input_file_stream(filename);
  assert(input_file_stream.is_open());
  std::stringstream buffer;
  buffer << input_file_stream.rdbuf();
  return buffer.str();
}

/**
 * Check if `byte` starts a UTF-8 codepoint.
 *
 * @param byte The byte to check.
 * @return True if `byte` starts a UTF-8 codepoint, false otherwise.
 */
#define is_utf8_start_byte(byte) ((byte & TWO_LEADING_BITS) != UTF8_NONSTART_BYTE_PREFIX)

/**
 * Count the number of UTF-8 codepoints between `begin` and `end`.
 *
 * @param begin A pointer to the first character of the string.
 * @param end A pointer to the character after the last character of the string.
 */
std::size_t utf8_distance(const char *begin, const char *end)
{
  int ncodepoints = 0;
  for (const char *c = begin; c < end; c++)
  {
    if (is_utf8_start_byte(*c))
    {
      ncodepoints++;
    }
  }
  return ncodepoints;
}

int main(int argc, const char *argv[])
{
  absl::InitializeLog();
  std::string pattern = read_file(argv[1]);
  RE2 re(pattern);
  std::string input_text = read_file(argv[2]);
  std::cout << "[regex]\npattern = '''" << pattern << "'''\n";
  std::cout << "input = '''" << input_text << "'''\n\n";
  absl::string_view input(input_text);
  int nsubmatches = re.NumberOfCapturingGroups() + 1;
  absl::string_view *submatch = new absl::string_view[nsubmatches];
  if (re.Match(input, 0, input.size(), RE2::UNANCHORED, submatch, nsubmatches))
  {
    std::cout << "[match_1]\n\n";
    for (int i = 0; i < nsubmatches; i++)
    {
      std::size_t ncodepoints = utf8_distance(submatch[i].data(), submatch[i].data() + submatch[i].size());
      std::size_t start_index = utf8_distance(input.data(), submatch[i].data());
      std::size_t end_index = start_index + ncodepoints;
      std::cout << "span = [" << start_index << ", " << end_index << "]\n"
                << "str = '''" << submatch[i] << "'''\n\n";
    }
  }
  else
  {
    std::cout << "# no match\n\n";
  }
  return 0;
}