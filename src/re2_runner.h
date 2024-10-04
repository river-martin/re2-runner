#ifndef RE2_RUNNER_H
#define RE2_RUNNER_H

#include "../re2/re2/re2.h"

/**
 * Check if `byte` starts a UTF-8 codepoint.
 *
 * @param byte The byte to check.
 * @return True if `byte` starts a UTF-8 codepoint, false otherwise.
 */
#define is_utf8_start_byte(byte) \
  ((byte & TWO_LEADING_BITS) != UTF8_NONSTART_BYTE_PREFIX)

// 1100
#define TWO_LEADING_BITS 0xC0
// 0100
#define UTF8_NONSTART_BYTE_PREFIX 0x80

/**
 * Count the number of UTF-8 codepoints between `begin` and `end`.
 *
 * @param begin A pointer to the first character of the string.
 * @param end A pointer to the character after the last character of the string.
 */
extern std::size_t utf8_distance(const char *begin, const char *end);

/**
 * Read the content of a file.
 *
 * @param filename The name of the file to read.
 * @return The content of the file as a string.
 */
extern std::string read_file(const char *filename);

extern bool match(RE2 *regex, absl::string_view input_text, int *nsubmatches,
                  absl::string_view **submatch);

#endif  // RE2_RUNNER_H