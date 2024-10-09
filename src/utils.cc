#include "utils.h"

#include <cassert>
#include <fstream>
#include <sstream>

namespace utils {

std::string read_file(std::string filename) {
  std::ifstream input_file_stream(filename);
  assert(input_file_stream.is_open());
  std::stringstream buffer;
  buffer << input_file_stream.rdbuf();
  return buffer.str();
}

}  // namespace utils