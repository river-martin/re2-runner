import re2
import io


def match_info_from_match(match, id=1):
    match_info = io.StringIO()
    match_info.write(f"[match_{id}]\n")
    match_info.write(
        f"\n[match_{id}.group_0]\nspan = {list(match.span())}\nstr = '''{match.group()}'''\n"
    )
    for i, group in enumerate(match.groups(), start=1):
        match_info.write(f"\n[match_{id}.group_{i}]\n")
        if group is None:
            match_info.write("# not captured\n")
            continue
        match_info.write(f"span = {list(match.span(i))}\nstr = '''{group}'''\n")
    return match_info.getvalue()


def parse_args():
    import argparse
    import textwrap

    parser = argparse.ArgumentParser(
        description="RE2 runner",
        usage="""re2_runner.py [options] <pattern> <input_file_path>""",
        # Keep the format of the epilog consistent with the above
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    parser.add_argument(
        "--posix_syntax",
        default=False,
        action="store_true",
        help="(false) restrict regexps to POSIX egrep syntax",
    )
    parser.add_argument(
        "--longest_match",
        default=False,
        action="store_true",
        help="(false) search for longest match, not first match",
    )
    parser.add_argument(
        "--log_errors",
        default=True,
        action="store_true",
        help="(true) log syntax and execution errors to ERROR",
    )
    parser.add_argument(
        "--max_mem",
        default=None,
        help="(see below) approx. max memory footprint of RE2",
    )
    parser.add_argument(
        "--literal",
        default=False,
        action="store_true",
        help="(false) interpret string as literal, not regexp",
    )
    parser.add_argument(
        "--never_nl",
        default=False,
        action="store_true",
        help="(false) never match \\n, even if it is in regexp",
    )
    parser.add_argument(
        "--dot_nl",
        default=False,
        action="store_true",
        help="(false) dot matches everything including new line",
    )
    parser.add_argument(
        "--never_capture",
        default=False,
        action="store_true",
        help="parse all parens as non-capturing",
    )
    parser.add_argument(
        "--case_sensitive",
        default=True,
        action="store_true",
        help="(true) match is case-sensitive (regexp can override with (?i) unless in posix_syntax mode)",
    )
    posix_syntax_group = parser.add_argument_group(
        "POSIX syntax options",
        textwrap.dedent(
            r"""
                The following options are only consulted when posix_syntax == true.
                When posix_syntax == false, these features are always enabled and
                cannot be turned off; to perform multi-line matching in that case,
                begin the regexp with (?m).
            """
        ),
    )
    posix_syntax_group.add_argument(
        "--perl_classes",
        default=False,
        action="store_true",
        help="(false) allow Perl's \\d \\s \\w \\D \\S \\W",
    )
    posix_syntax_group.add_argument(
        "--word_boundary",
        default=False,
        action="store_true",
        help="(false) allow Perl's \\b \\B (word boundary and not)",
    )
    posix_syntax_group.add_argument(
        "--one_line",
        default=False,
        action="store_true",
        help="(false) ^ and $ only match beginning and end of text",
    )

    parser.add_argument(
        "regex_file_path", help="A path to the file containing the regex"
    )
    parser.add_argument(
        "input_file_path", help="A path to a file containing the text to search"
    )

    epilog = r"""
        The max_mem option controls how much memory can be used
        to hold the compiled form of the regexp (the Prog) and
        its cached DFA graphs.  Code Search placed limits on the number
        of Prog instructions and DFA states: 10,000 for both.
        In RE2, those limits would translate to about 240 KB per Prog
        and perhaps 2.5 MB per DFA (DFA state sizes vary by regexp; RE2 does a
        better job of keeping them small than Code Search did).
        Each RE2 has two Progs (one forward, one reverse), and each Prog
        can have two DFAs (one first match, one longest match).
        That makes 4 DFAs:

            forward, first-match    - used for UNANCHORED or ANCHOR_START searches
                                        if opt.longest_match() == false
            forward, longest-match  - used for all ANCHOR_BOTH searches,
                                        and the other two kinds if
                                        opt.longest_match() == true
            reverse, first-match    - never used
            reverse, longest-match  - used as second phase for unanchored searches

        The RE2 memory budget is statically divided between the two
        Progs and then the DFAs: two thirds to the forward Prog
        and one third to the reverse Prog.  The forward Prog gives half
        of what it has left over to each of its DFAs.  The reverse Prog
        gives it all to its longest-match DFA.

        Once a DFA fills its budget, it flushes its cache and starts over.
        If this happens too often, RE2 falls back on the NFA implementation.
    """

    parser.epilog = textwrap.dedent(epilog)

    return parser.parse_args()


if __name__ == "__main__":
    args = parse_args()
    options = re2.Options()
    for key, value in args._get_kwargs():
        if value is None:
            continue
        if hasattr(options, key):
            setattr(options, key, value)
        else:
            assert key == "regex_file_path" or key == "input_file_path"
    with open(args.regex_file_path, "r") as f:
        regex = f.read()
    with open(args.input_file_path, "r") as f:
        text = f.read()
    match = re2.match(regex, text)
    if match is not None:
        print(match_info_from_match(match))
    else:
        print("# no match")
