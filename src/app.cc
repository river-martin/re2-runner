#include "re2_runner.h"

#include "absl/log/initialize.h"
#include <iostream>

int main(int argc, const char *argv[])
{
  absl::InitializeLog();
  std::string pattern = read_file(argv[1]);
  std::string input_text = read_file(argv[2]);
  RE2 regex(pattern);
  absl::string_view input(input_text);
  std::cout << "[regex]\npattern = '''" << pattern << "'''\n";
  std::cout << "input = '''" << input_text << "'''\n\n";
  int nsubmatches;
  absl::string_view *submatch;
  if (match(&regex, input, &nsubmatches, &submatch))
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