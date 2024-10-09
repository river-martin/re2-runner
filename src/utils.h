#ifndef _UTILS_H
#define _UTILS_H
#include <fstream>
#include <string>

namespace utils {
/**
 * Read the content of a file.
 *
 * @param filename The name of the file to read.
 * @return The content of the file as a string.
 */
extern std::string read_file(std::string filename);
}  // namespace utils
#endif