#ifndef _RE2_RUNNER_H_
#define _RE2_RUNNER_H_

#include <string>

#include "absl/log/initialize.h"

/**
 * Print match information in TOML format.
 *
 * @param s The input string.
 * @param submatch The array of submatches.
 * @param nsubmatch The number of capture groups + 1 (for the whole match).
 */
void print_match_info(const std::string &s, std::string_view *submatch,
                      int nsubmatch);

/**
 * Run a regular expression pattern on a string and print the match information.
 */
extern void run_and_print_match_info(const std::string &pattern,
                                     const std::string &s);

#endif