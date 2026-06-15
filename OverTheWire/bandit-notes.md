# OverTheWire: Bandit — Walkthrough Notes

> Personal notes from the Bandit wargame. Each level introduces a new Linux concept or command. Notes include what I tried, what failed, why, and what the correct approach was.

---

## Connecting to the server

```bash
ssh bandit.labs.overthewire.org -p 2220 -l bandit0
# Replace bandit0 with the level you are logging into
# Default password for level 0: bandit0
```

---

## Level 0 → 1

Password stored in a file called `readme` in the home directory.

```bash
ls
cat readme
```

`ls` lists files in the current directory. `cat` prints the contents of a file to the terminal.

---

## Level 1 → 2

Password stored in a file called `-`.

```bash
# This does not work — the shell interprets - as stdin
cat -

# These work
cat ./-
cat -- "-"
```

`./` means "current directory". Prefixing the filename with `./` tells the shell it is a file path, not a flag. Without it, `cat -` reads from standard input and waits indefinitely.

---

## Level 2 → 3

Password stored in a file called `spaces in this filename`.

```bash
cat 'spaces in this filename'
cat "spaces in this filename"
cat spaces\ in\ this\ filename
```

Quotes treat everything inside as a single argument. A backslash before a space escapes it. Tab completion in the shell also handles this automatically.

---

## Level 3 → 4

Password stored in a hidden file inside the `inhere` directory.

```bash
cd inhere
ls        # shows nothing
ls -a     # shows hidden files (those starting with .)
cat ./.hidden
```

In Linux, files and directories starting with `.` are hidden by default. `ls` does not show them without the `-a` (all) flag.

---

## Level 4 → 5

Password stored in the only human-readable file in the `inhere` directory. The rest are binary.

```bash
cd inhere
file ./*
```

`file` identifies the type of each file. Look for the one described as `ASCII text`. Binary files will show `data` or an executable format.

```bash
cat ./-file07   # whichever file shows as ASCII text
```

---

## Level 5 → 6

Password is in a file somewhere under `inhere` that is human-readable, exactly 1033 bytes, and not executable.

```bash
find . -type f -size 1033c ! -executable
```

`-type f` limits results to files only. `-size 1033c` matches exactly 1033 bytes (`c` = bytes). `! -executable` excludes executable files.

I initially tried `du` to check sizes, which was wrong — `du` shows disk usage for directories, not precise file sizes. `find -size` is the right tool.

---

## Level 6 → 7

Password is somewhere on the server. File properties: owned by user `bandit7`, owned by group `bandit6`, 33 bytes in size.

```bash
find / -user bandit7 -group bandit6 -size 33c 2>/dev/null
```

Searching from `/` (root) covers the entire filesystem. Most paths will return "Permission denied" — `2>/dev/null` redirects error messages to /dev/null and hides them, leaving only useful results.

The mistake I made: using `-name bandit7` which searches for a filename, not a file owner. `-user` is the correct flag for ownership.

---

## Level 7 → 8

Password is in `data.txt` next to the word `millionth`.

```bash
grep millionth data.txt
```

`grep` searches for a pattern in a file and prints matching lines. `^` anchors to the start of a line and `$` anchors to the end — neither was needed here because `millionth` appears at the start of the line but the file is searched correctly without anchoring.

---

## Level 8 → 9

Password is the only line in `data.txt` that appears exactly once.

```bash
sort data.txt | uniq -u
```

`uniq -u` outputs only lines that are not repeated. The critical point: `uniq` only compares adjacent lines. Without sorting first, duplicate lines scattered throughout the file would all appear "unique" to `uniq`. Sorting brings identical lines next to each other before `uniq` processes them.

```bash
# This does not work correctly on unsorted input
uniq -u data.txt

# This works
sort data.txt | uniq -u
```

---

## Level 9 → 10

Password is in `data.txt` among human-readable strings, preceded by several `=` characters. The file is binary.

```bash
strings data.txt | grep '=='
```

Running `grep` directly on a binary file returns only "Binary file matches" without showing the content. `strings` extracts printable ASCII sequences from a binary file first, then `grep` filters those results.

---

## Level 10 → 11

Password is in `data.txt` encoded with Base64.

```bash
base64 -d data.txt
```

Base64 is encoding, not encryption. It is reversible without a key — it only changes the representation of data. The encoded string typically ends with `=` or `==` padding. `-d` decodes; without it, `base64` would encode the file again.

---

## Level 11 → 12

Password is in `data.txt` with all letters rotated by 13 positions (ROT13).

```bash
cat data.txt | tr 'A-Za-z' 'N-ZA-Mn-za-m'
```

ROT13 shifts each letter 13 places in the alphabet. Since the alphabet has 26 letters, applying ROT13 twice returns the original text. It is a simple substitution cipher — not encryption.

`tr` translates characters from one set to another. `'A-Za-z'` is the input set (all letters). `'N-ZA-Mn-za-m'` is the output set — the same letters shifted by 13.

Common mistakes:
- using only uppercase or only lowercase — both must be handled
- using `&&` inside the character sets — `&&` is a shell operator, not valid inside `tr` sets
- trying to write to a file in a directory where the current user lacks write permission

---

## Command reference

```bash
# Navigation
ls              # list files
ls -a           # list all including hidden
ls -la          # long format, all files
cd directory    # change directory
pwd             # print working directory

# Reading files
cat file        # print file contents
cat ./file      # use when filename starts with - or is ambiguous

# Finding files
find . -type f                         # all files recursively
find . -name "*.txt"                   # by filename pattern
find / -user X -group Y -size 33c      # by owner, group, size
find . -size 1033c ! -executable       # by size, excluding executables
find . -exec grep -H 'pattern' {} \;   # find then run grep on each result

# Searching within files
grep 'pattern' file                    # find lines matching pattern
grep '^pattern' file                   # lines starting with pattern
grep -H 'pattern' file                 # include filename in output

# Sorting and deduplication
sort file                              # sort lines alphabetically
sort file | uniq -u                    # lines that appear exactly once
uniq -c file                           # count occurrences per line

# Binary files
file filename                          # identify file type
strings filename                       # extract printable strings

# Encoding
base64 file                            # encode to Base64
base64 -d file                         # decode from Base64
cat file | tr 'A-Za-z' 'N-ZA-Mn-za-m' # ROT13

# Redirecting output
2>/dev/null     # discard error messages
cmd1 | cmd2     # pipe output of cmd1 as input to cmd2
cmd < file      # use file contents as input to cmd
```

---

## References

- [OverTheWire: Bandit](https://overthewire.org/wargames/bandit/)
