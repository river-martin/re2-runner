#include <iostream>
#include <string>

#include "../re2/re2/prog.h"
#include "../re2/re2/re2.h"
#include "../re2/re2/regexp.h"
#include "absl/strings/str_format.h"
#include "utils.h"

// Note: copied from re2/re2/prog.cc, with the `id` parameter removed.
static std::string FlattenedProgToString(re2::Prog *prog) {
  std::string s;
  for (int id = prog->start_unanchored(); id < prog->size(); id++) {
    re2::Prog::Inst *ip = prog->inst(id);
    if (ip->last())
      s += absl::StrFormat(". %s\n", ip->Dump());
    else
      s += absl::StrFormat("+ %s\n", ip->Dump());
  }
  return s;
}

std::string pattern_to_prog_string(const std::string &pattern) {
  RE2 regex(pattern);
  re2::Regexp *regexp = regex.Regexp();
  re2::Prog *prog = regexp->CompileToProg(0);
  prog->Flatten();
  return FlattenedProgToString(prog);
}

std::string pattern_to_reverse_prog_string(const std::string &pattern) {
  RE2 regex(pattern);
  re2::Regexp *regexp = regex.Regexp();
  re2::Prog *reverse_prog = regexp->CompileToReverseProg(0);
  reverse_prog->Flatten();
  return FlattenedProgToString(reverse_prog);
}

int main(int argc, const char *argv[]) {
  if (argc != 2 && argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <pattern-file> [reverse]\n";
    return EXIT_FAILURE;
  }
  const std::string pattern = utils::read_file(std::string(argv[1]));
  if (argc == 3) {
    assert(std::string(argv[2]) == "reverse");
    std::cout << "; reverse prog" << std::endl;
    std::cout << pattern_to_reverse_prog_string(pattern) << std::endl;
    return EXIT_SUCCESS;
  }
  std::cout << "; forward prog" << std::endl;
  std::cout << pattern_to_prog_string(pattern) << std::endl;
  return EXIT_SUCCESS;
}