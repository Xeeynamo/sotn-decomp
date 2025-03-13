# I'm not fluent in markdown, so I'm not going to mess with it.  If anybody wants to improve this readme, please do.
permuter_loader.py is just a loader for decomp-permuter to address the hurdles that decomp-permuter presents for standardized use within sotn-decomp.

For the expected usage, OVL is the overlay as it is written in the splat config (i.e. stlib) and subsegment is the name of the c subsegment as set in the splat config (no .c extension).  The -p or --permuter arguments is an optional way to import and permute with a single command.

expected usage:
tools/sotn_permuter/permuter_loader.py import {SUBSEGMENT} {FUNCTION} -o {OVL}
tools/sotn_permuter/permuter_loader.py permute {FUNCTION}
tools/sotn_permuter/permuter_loader.py clean {FUNCTION|all}


When using the -o or --overlay argument, any previously imported version of the same name will be overwritten.  Omitting the -o argument will need the full path passed and will not automatically permute even if the -p argument is passed.  It will also append a number to the name if a directory for the function already exists.


legacy usage:
It passes any arguments except --version and import|permute directly to import.py and permuter.py as appropriate.
tools/sotn_permuter/permuter_loader.py import {path_to_c_file} {path_to_s_file}
tools/sotn_permuter/permuter_loader.py permute tools/sotn_permuter/permute.me/{func_name}


permuter_loader.py arguments
usage: permuter_loader.py [-h] [--version VERSION] {import,permute} [import.py or permuter.py args as appropriate]

Use decomp-permuter with sotn specific adjustments

positional arguments:
  {import,permute,clean}
                        Whether to import or permute the function
    import              Import a function to be permuted
    permute             Permute a function
    clean               Clean function folders from permuter

options:
  -h, --help         show this help message and exit
  --version VERSION  Sets game version and overrides VERSION environment variable

usage: permuter_loader.py import [-h] [-o OVERLAY] [-p] source function

positional arguments:
  source                The name specified for the splat subsegment or the source filename if not using --overlay
  function              The function to be permuted or the function asm filename if not using --overlay

options:
  -h, --help            show this help message and exit
  -o OVERLAY, --overlay OVERLAY
                        Specifies the overlay name where the function exists, as it is in the splat config filename, and causes the loader to treat the positional arguments
                        as subsegment and function.
  -p, --permute         Begins permuting immediately after the function is imported

usage: permuter_loader.py permute [-h] function

positional arguments:
  function    The function to be permuted

options:
  -h, --help  show this help message and exit

usage: permuter_loader.py clean [-h] function

positional arguments:
  function    The function to be cleaned, or use "all" to clean all folders

options:
  -h, --help  show this help message and exit


decomp-permuter arguments:
import.py arguments
usage: import.py [-h] [--keep] [--preserve-macros REGEX] [--no-prune] [--decompme] [--settings SETTINGS_FILE] c_file {asm_file|func_name} [make_flags ...]

Import a function for use with the permuter. Will create a new directory nonmatchings/<funcname>-<id>/.

positional arguments:
  c_file                File containing the function. Assumes that the file can be built with 'make' to create an .o file.
  {asm_file|func_name}  File containing assembly for the function. Must start with 'glabel <function_name>' and contain no other functions. Alternatively, a function name can be given, which will be looked for in all GLOBAL_ASM blocks in the C
                        file.
  make_flags            Arguments to pass to 'make'. PERMUTER=1 will always be passed.

options:
  -h, --help            show this help message and exit
  --keep                Keep the directory on error.
  --preserve-macros REGEX
                        Regex for which macros to preserve, or empty string for no macros. By default, this is read from permuter_settings.toml, tools/permuter_settings.toml or config/permuter_settings.toml in a parent directory of the imported
                        file. Type information is also read from this file.
  --no-prune            Don't minimize the source to keep only the imported function and functions/struct/variables that it uses. Normally this behavior is useful to make the permuter faster, but in cases where unrelated code affects the generated
                        assembly asm it can be necessary to turn off. Note that regardless of this setting the permuter always removes all other functions by replacing them with declarations.
  --decompme            Upload the function to decomp.me to share with other people, instead of importing.
  --settings SETTINGS_FILE
                        Path to settings file.

    
permuter arguments
usage: permuter.py [-h] [--help=randomization-passes] [--show-errors] [--show-timings] [--print-diffs] [--abort-exceptions] [--better-only] [--best-only] [--stop-on-zero] [--quiet] [--stack-diffs] [--algorithm {difflib,levenshtein}] [--keep-prob PROB] [-j THREADS] [-J] [--pah-debug] [--priority PRIORITY] [--no-context-output] [--only-if-below SCORE_THRESHOLD] [--debug] [--speed [1-100]] directory [directory ...]

Randomly permute C files to better match a target binary.

positional arguments:
    directory       Directory containing base.c, target.o and compile.sh. Multiple directories may be given.

options:
  -h, --help            show this help message and exit
  --help=randomization-passes
                        Show documentation for all the available randomization passes.
  --show-errors         Display compiler error/warning messages, and keep .c files for failed compiles.
  --show-timings        Display the time taken by permuting vs. compiling vs. scoring.
  --print-diffs         Instead of compiling generated sources, display diffs against a base version.
  --abort-exceptions    Stop execution when an internal permuter exception occurs.
  --better-only         Only report scores better than the base.
  --best-only           Only report ties or new high scores.
  --stop-on-zero        Stop after producing an output with score 0.
  --quiet               Don't print a status line with the number of iterations.
  --stack-diffs         Take stack differences into account when computing the score.
  --algorithm           Diff algorithm to use, difflib or levenshtein.
  --keep-prob           Continue randomizing the previous output with the given probability, 0.0 to 1.0.
  -j                    Number of own threads to use (default: 1 without -J, 0 with -J).
  -J                    Harness extra compute power through cyberspace (permuter@home).
  --pah-debug           Enable debug prints for permuter@home
  --priority            Proportion of server resources to use when multiple people
                        are using -J at the same time.
                        Defaults to 1.0, meaning resources are split equally, but can be
                        set to any value within [{MIN_PRIO}, {MAX_PRIO}].
                        Each server runs with a priority threshold, which defaults to 0.1,
                        below which they will not run permuter jobs at all.
  --no-context-output"  Removes all text above the target function in the output source files.
  --only-if-below       Only report scores better (lower) than this value.
  --debug               Debug mode, only compiles and scores the base for debugging issues.
  --speed               Speed% to run at to reduce resources. Default 100

undocumented options:
  --seed                Forces a seed value for permuter.